#include "MUD_Engine.h"
MUD_Engine::MUD_Engine()
{
	EXP_Table.parseTable("/data/LV_EXP.json");
	Mon_Table.parseTable("/data/Monster.json");
	UID_Table.parseTable("/data/UID.json");
	Pot_Table.parseTable("/data/Item_Potion.json");
	EQ_Table.parseTable("/data/Item_Equipment.json");
}

void MUD_Engine::player_login(Player* player)
{
	Map.AddUID(player->Get_Position(), player->Get_UID());
	Role_Map.insert(player->Get_UID(), player);

}
void MUD_Engine::player_logout(Player* player)
{
	Map.RemoveUID(player->Get_Position(), player->Get_UID());
	Role_Map.remove(player->Get_UID());
}
void MUD_Engine::player_update(Player* player)
{
	player->total_ATK = player->Get_ATK();
	player->total_DEF = player->Get_DEF();
	player->total_HPMAX = player->Get_HPMAX();
	player->total_MPMAX = player->Get_MPMAX();

	for (auto it = player->Eqs_Using.constBegin(); it != player->Eqs_Using.constEnd(); ++it) {
		//qDebug() << "Equipment Part:" << it.key() << ", Equipment ID:" << it.value();
		Item_Equipment EQ;
		EQ_Table.Get_Equipment(it.value(), EQ);
		player->total_ATK	+= EQ.Get_ATK();
		player->total_DEF	+= EQ.Get_DEF();
		player->total_HPMAX += EQ.Get_HP();
		player->total_MPMAX += EQ.Get_MP();
	}
}

void MUD_Engine::auto_Battling(MassageData& p_massagedata, BattleRoom& room)
{
	QString str;
	str += "第" + QString::number(room.round++) + "回合\n";
	p_massagedata.m_errorcode = Errorcode_OK;
	Role* player_role = Get_Role(room.Player_UID);
	Player* player = dynamic_cast<Player*>(player_role);
	if (player->Get_playstate() != Player_Battle)
		return; //未處於戰鬥中須做更多狀況排除
	//return;
	Role* mon_role = Get_Role(room.Monster_UID);
	Monster* mon = dynamic_cast<Monster*>(mon_role);
	if (player && mon)
	{
		switch (player->Get_BattleState())
		{
		case Battle_Attack:
			player->Attack(mon, str);
			break;
		case Battle_Item:

			break;
		case Battle_Run:
		{
			std::srand(static_cast<unsigned int>(std::time(nullptr)));
			int random = std::rand() % 2;
			if (random == 1)
			{
				//逃跑成功
				str += "<font color=\"yellow\">逃跑成功\</font>\n";
				player->Bettle_end();
			}
			else
			{
				str += "<font color=\"red\">逃跑失敗\</font>\n";
			}

			break;
		}
		default:
			break;
		}
		if (mon->Get_HP() <= 0)
		{
			//怪物死掉
			str += mon->Get_NAME() + " 死亡\n";
			std::srand(static_cast<unsigned int>(std::time(nullptr)));
			int random = std::rand() % 100 + 1;
			if (random >= mon->Get_DropChance()) {
				//掉落物品
				str += mon->Get_NAME() + "掉落了東西\n";
				std::srand(static_cast<unsigned int>(std::time(nullptr) + 817));
				random = std::rand() % 100 + 1;
				for (auto item : mon->Get_DropList()) {
					int itemid = item.first;
					int probability = item.second;
					if (random <= probability) {
						if (itemid >= EQUIPMENT_UID_START && itemid <= EQUIPMENT_UID_END)
						{
							Item_Equipment EQ;
							EQ_Table.Get_Equipment(static_cast<Item_EquipmentID>(itemid), EQ);
							player->Backpack_Put(EQ.Get_ItemID(), str);
							str += EQ.Get_NAME() + "\n"; //接續Backpack_Put文字
						}
						else if (itemid >= POTION_UID_START && itemid <= POTION_UID_END)
						{
							Item_Potion Pot;
							Pot_Table.Get_Potion(static_cast<Item_PotionID>(itemid), Pot);
							player->Backpack_Put(Pot.Get_ItemID(), str);
							str += Pot.Get_NAME() + "\n"; //接續Backpack_Put文字
						}
						break;
					}
					random -= probability;
				}
			}
			player->Add_EXP(mon->Get_EXP(), str);
			player->Add_Money(mon->Get_Money(), str);
			player->Check_LVUP(EXP_Table.GetEXP(player->Get_LV()), str);
			player->Bettle_end();

		}
		else
		{
			mon->Attack(player, str);
			if (player->Get_HP() <= 0)
			{
				//玩家死亡
				str += "<font color=\"red\">你死了!!!!\</font>\n";
				QPoint resetpog = QPoint(6, 6);
				player->Set_Position(resetpog);
				player->Lose_EXP(EXP_Table.GetEXP(player->Get_LV()) / 10, str);
				player->Lose_Money(player->Get_Money(), str);
				player->Bettle_end();
			}
		}
		if (mon->Get_HP() <= 0) //最後才刪除怪物
		{
			Die_Role(mon->Get_UID());
			player->Bettle_end();
		}

		
	}
	p_massagedata.m_Data["GameText"] = str;

}

void MUD_Engine::Scenes_Info(MassageData& p_massagedata,Player* player, int& Minorcommand)
{
	QString str;
	switch (player->Get_playstate())
	{
		p_massagedata.m_Data["Can_move"] = false;
	case Player_Idle: {
		p_massagedata.m_Data["Can_move"] = true;
		switch (Map.getSceneID(player->Get_Position()))
		{
		case Impassable: {
			str = "不應該位於當前地點";
			break;
		}
		case Village: {
			str += "==小鎮==\n";
			str += "一個寧靜的小鎮,有許多房子和人,";
			break;
		}
		case Way: {
			str += "==道路==\n";
			str += "一個平坦的道路,旁邊似乎有甚麼東西,";
			break;
		}
		case Forest: {
			str += "==森林==\n";
			str += "一個幽暗的森林,看不到太遠的地方,";
			break;
		}
		case Ruins: {
			str += "==廢墟==\n";
			str += "一個殘破的廢墟,之前有許多房子和人,";
			break;
		}
		case RuinsBoss: {
			str += "==廢墟Boss==\n";
			str += "前方就是惡龍所在的地方,準備好挑戰了嗎,";
			break;
		}
		default:
			p_massagedata.m_errorcode = Errorcode_GAME_UNKNOWCOMMAND;
			break;
		}
		Show_Path(player->Get_Position(),str);

		if (Map.getSceneID(player->Get_Position()) == Impassable)
		{

		}
		else if (Map.getSceneID(player->Get_Position()) == Village)
		{
			//安全區域
			str += "1.移動說明";
			str += "2.打開背包";
			str += "3.去商店";
			str += "4.休息";
			str += "5.角色資訊\n";
		}
		else if (Map.getSceneID(player->Get_Position())!= Village)
		{
			//危險區域
			if (Map.GetUIDList(player->Get_Position()).size() > 1)
			{
				str += "<font color=\"yellow\">!!!這裡似乎有東西在動!!!</font>\n";

			}
			str += "1.移動說明";
			str += "2.觀察";
			str += "3.攻擊";
			str += "4.打開背包";
			str += "5.角色資訊\n";
			//str += "5.使用裝備\n";

		}
		break;
	}
	//case Player_Move: {
	//	str = "想要往哪裡移動";
	//	Show_Path(player->Get_Position(), str);
	//	str += "0.取消 ";
	//	str += "w.上 ";
	//	str += "s.下 ";
	//	str += "a.左 ";
	//	str += "d.右\n";
	//	break;
	//}
	case Player_Observe: {
		str = "想要觀察誰\n";
		str += "0.取消";
		int i = 1;
		for each (int UID in Map.GetUIDList(player->Get_Position()))
		{
			if (UID < MONSTER_UID_START || UID > MONSTER_UID_END)
				continue;
			Role* role = Get_Role(UID);
			Monster * mon = dynamic_cast<Monster*>(role);
			if (mon)
			{
				str += QString::number(i++) + "." + mon->Get_NAME();
				player->Add_SightRole(UID);
			}
		}
		str += "\n";
		break;
	}
	case Player_Attack: {
		str = "想要攻擊誰\n";
		str += "0.取消";
		int i = 1;
		for each (int UID in Map.GetUIDList(player->Get_Position()))
		{
			if (UID < MONSTER_UID_START || UID > MONSTER_UID_END)
				continue;
			Role* role = Get_Role(UID);
			Monster* mon = dynamic_cast<Monster*>(role);
			if (mon)
			{
				str += QString::number(i++) + "." + mon->Get_NAME();
				player->Add_SightRole(UID);
			}
		}
		str += "\n";
		break;
	}
	case Player_Battle: {
		str = "想要做甚麼\n";
		switch (player->Get_BattleState())
		{
		case Battle_Attack:
			str += "1.逃跑";
			break;
		case Battle_Item:
			break;
		case Battle_Run:
		{
			str += "1.取消逃跑";
			break;
		}
		default:
			break;
		}
		break;
	}
	case Player_Backpack: {
		str = "想要做甚麼\n";
		str += "0.取消";
		str += "1.背包清單";
		str += "2.身上裝備";
		str += "3.使用物品";
		str += "4.丟棄物品\n";
		break;
	}
	case Player_UseItem: {
		str = "想要使用甚麼\n";
		str += "0.取消";
		int i = 1;
		for each (int itemid in player->Backpack)
		{
			if (itemid >= EQUIPMENT_UID_START && itemid <= EQUIPMENT_UID_END)
			{
				Item_Equipment EQ;
				EQ_Table.Get_Equipment(static_cast<Item_EquipmentID>(itemid), EQ);
				str += QString::number(i++) + "." + EQ.Get_NAME() ;

			}
			else if (itemid >= POTION_UID_START && itemid <= POTION_UID_END)
			{
				Item_Potion Pot;
				Pot_Table.Get_Potion(static_cast<Item_PotionID>(itemid), Pot);
				str += QString::number(i++) + "." + Pot.Get_NAME();
			}
		}
		str += "\n";
		break;
	}
					   
	case Player_DropItem: {
		str = "想要丟棄甚麼\n";
		str += "0.取消";
		int i = 1;
		for each (int itemid in player->Backpack)
		{
			if (itemid >= EQUIPMENT_UID_START && itemid <= EQUIPMENT_UID_END)
			{
				Item_Equipment EQ;
				EQ_Table.Get_Equipment(static_cast<Item_EquipmentID>(itemid), EQ);
				str += QString::number(i++) + "." + EQ.Get_NAME();

			}
			else if (itemid >= POTION_UID_START && itemid <= POTION_UID_END)
			{
				Item_Potion Pot;
				Pot_Table.Get_Potion(static_cast<Item_PotionID>(itemid), Pot);
				str += QString::number(i++) + "." + Pot.Get_NAME();
			}
		}
		str += "\n";
		break;
	}
	case Player_GoStore: {
		str = "要去哪間商店\n";
		str += "0.取消";
		int i = 1;

		if (Map.is_Store(Store_Weapon, player->Get_Position()))
		{
			str += QString::number(i++) + ".武器店";
			player->Add_SightRole(Store_Weapon);

		}
		if (Map.is_Store(Store_Armor, player->Get_Position()))
		{
			str += QString::number(i++) + ".防具店";
			player->Add_SightRole(Store_Armor);

		}
		if (Map.is_Store(Store_Potion, player->Get_Position()))
		{
			str += QString::number(i++) + ".藥水店";
			player->Add_SightRole(Store_Potion);
		}
		str += QString::number(i++) + ".出售背包物品\n";
		player->Add_SightRole(Store_Sell);
		break;
	}
	case Player_Shopping: {
		str = "想要買甚麼\n";
		str += "0.取消";
		int i = 1;
		for each (int itemid in player->Get_SightRole() )
		{
			if (itemid >= EQUIPMENT_UID_START && itemid <= EQUIPMENT_UID_END)
			{
				Item_Equipment EQ;
				EQ_Table.Get_Equipment(static_cast<Item_EquipmentID>(itemid), EQ);
				str += QString::number(i++) + "." + EQ.Get_NAME() + "";
			}
			else if (itemid >= POTION_UID_START && itemid <= POTION_UID_END)
			{
				Item_Potion Pot;
				Pot_Table.Get_Potion(static_cast<Item_PotionID>(itemid), Pot);
				str += QString::number(i++) + "." + Pot.Get_NAME() + "";
			}
		}
		str += "\n";
		break;
	}
	case Player_Selling: {
		str = "想要販賣甚麼\n";
		str += "0.取消";
		int i = 1;
		for each (int itemid in player->Backpack)
		{
			if (itemid >= EQUIPMENT_UID_START && itemid <= EQUIPMENT_UID_END)
			{
				Item_Equipment EQ;
				EQ_Table.Get_Equipment(static_cast<Item_EquipmentID>(itemid), EQ);
				str += QString::number(i++) + "." + EQ.Get_NAME();

			}
			else if (itemid >= POTION_UID_START && itemid <= POTION_UID_END)
			{
				Item_Potion Pot;
				Pot_Table.Get_Potion(static_cast<Item_PotionID>(itemid), Pot);
				str += QString::number(i++) + "." + Pot.Get_NAME();
			}
		}
		str += "\n";
		break;
	}
	default:
		p_massagedata.m_errorcode = Errorcode_GAME_UNKNOWCOMMAND;
		break;
	}
	p_massagedata.m_Data["ScenesInfo"] = str;
	p_massagedata.m_errorcode = Errorcode_OK;
	p_massagedata.m_Time = QDateTime::currentDateTime();

}
void MUD_Engine::play(MassageData& p_massagedata,Player* player,int& Minorcommand)
{
	QString str ;

	switch (player->Get_playstate())
	{
		p_massagedata.m_Data["Can_move"] = false;
	case Player_Idle: {
		idle(p_massagedata, str, player, Minorcommand);
		p_massagedata.m_Data["Can_move"] = true; //只有Idle可以移動
		break;
	}
	//case Player_Move: {
	//	str += "==移動==\n";
	//	Move(p_massagedata, str, player, Minorcommand);
	//	break;
	//}
	case Player_Observe: {
		str += "==觀察==\n";
		Observe(p_massagedata, str, player, Minorcommand);
		break;
	}
	case Player_Attack: {
		str += "==攻擊==\n";
		Attack(p_massagedata, str, player, Minorcommand);
		break;
	}
	case Player_Backpack: {
		str += "==打開背包==\n";
		Backpack(p_massagedata, str, player, Minorcommand);
		break;
	}
	case Player_UseItem: {
		str += "==使用物品==\n";
		UseItem(p_massagedata, str, player, Minorcommand);
		break;
	}
	case Player_DropItem: {
		str += "==丟棄物品==\n";
		DropItem(p_massagedata, str, player, Minorcommand);
		break;
	}
	//case Player_UseEQ: {
	//	str += "==使用裝備==\n";
	//	UseEQ(p_massagedata, str, player, Minorcommand);
	//	break;
	//}
	case Player_GoStore: {
		str += "==進入商店==\n";
		Store(p_massagedata, str, player, Minorcommand);
		break;
	}
	case Player_Shopping: {
		str += "==購物中==\n";
		Shopping(p_massagedata, str, player, Minorcommand);
		break;
	}
	case Player_Selling: {
		str += "==販賣東西==\n";
		Selling(p_massagedata, str, player, Minorcommand);
		break;
	}
	case Player_Battle: {
		str += "==戰鬥中==\n";
		Battling(p_massagedata, str, player, Minorcommand);
		break;
	}
	default:
		p_massagedata.m_errorcode = Errorcode_GAME_UNKNOWCOMMAND;
		break;
	}
	p_massagedata.m_Data["GameText"] = str;
	p_massagedata.m_Time = QDateTime::currentDateTime();
	player_update(player);
}

void MUD_Engine::Spawn_BattleRoom(int player_UID, int monster_UID)
{
	Role* role = Get_Role(monster_UID);
	Monster* mon = dynamic_cast<Monster*>(role);
	if (mon)
	{
		BattleRoom room = BattleRoom(player_UID, monster_UID);
		BattleRoom_List.append(room);
	}


}
void MUD_Engine::Spawn_Monsters(MonsterID MID, QPoint pos)
{
	Monster* Mons = new Monster;
	Mon_Table.Get_Monster(MID, *Mons);
	Mons->Set_UID(UID_Table.GetMonsterUID());
	Mons->Set_Position(pos);
	Map.AddUID(pos, Mons->Get_UID());
	Role_Map.insert(Mons->Get_UID(),Mons);
}

Role* MUD_Engine::Get_Role(int UID)
{
	Role* role = Role_Map.value(UID);

	if (role) {
		// 嘗試將 Role* 轉換為 Player*
		Player* player = dynamic_cast<Player*>(role);

		if (player) {
			return player;
		}
		else {
			Monster* monster = dynamic_cast<Monster*>(role);
			if (monster) {
				return monster;
			}
			else {
				return NULL;
			}

		}
	}
	else {
		// 找不到指定 UID 的 Role
		return NULL;
	}
}
void MUD_Engine::Die_Role(int UID)
{
	Role* role = Role_Map.value(UID);
	Map.RemoveUID(role->Get_Position(), role->Get_UID());
	Role_Map.remove(UID);

	delete role;
}

void MUD_Engine::idle(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand)
{
	if (Map.getSceneID(player->Get_Position()) == Village)
	{
		// 安全區域
		switch (Minorcommand)
		{
		case 0: {
			player->Set_playstate(Player_Idle);
			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}
		case 1: {
			str += "直接使用WASD移動\n";
			//player->Set_playstate(Player_Move);
			player->Set_playstate(Player_Idle);
			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}
		case 2: {
			player->Set_playstate(Player_Backpack);

			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}
		case 3: {
			player->Set_playstate(Player_GoStore);

			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}
		case 4: {
			str += "在村莊中休息\n";
			player->Rest(str);

			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}
		case 5: {
			Show_Player(player, str);
			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}
		case 101: {
			Move(p_massagedata, str, player, 1);
			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}
		case 102: {
			Move(p_massagedata, str, player, 2);
			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}		
		case 103: {
			Move(p_massagedata, str, player, 3);
			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}		
		case 104: {
			Move(p_massagedata, str, player, 4);
			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}
		default: {
			//str += "錯誤指令\n";
			p_massagedata.m_errorcode = Errorcode_OK;
		}
			   break;
		}
	}
	else
	{
		// 危險區域
		switch (Minorcommand)
		{
		case 0: {
			player->Set_playstate(Player_Idle);
			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}
		case 1: {
			str += "直接使用WASD移動\n";
			//player->Set_playstate(Player_Move);
			player->Set_playstate(Player_Idle);
			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}
		case 2: {
			player->Set_playstate(Player_Observe);

			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}
		case 3: {
			player->Set_playstate(Player_Attack);

			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}
		case 4: {
			player->Set_playstate(Player_Backpack);

			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}
		case 5: {
			Show_Player(player, str);
			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}
		case 101: {
			Move(p_massagedata, str, player, 1);
			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}
		case 102: {
			Move(p_massagedata, str, player, 2);
			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}
		case 103: {
			Move(p_massagedata, str, player, 3);
			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}
		case 104: {
			Move(p_massagedata, str, player, 4);
			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}

		default: {
			//str += "錯誤指令\n";
			p_massagedata.m_errorcode = Errorcode_OK;
		}
			   break;
		}
	}

}
void MUD_Engine::Move(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand)
{
	QPoint pos = player->Get_Position();
	QPoint nextpos;

	switch (Minorcommand)
	{
	case 0: {
		p_massagedata.m_errorcode = Errorcode_OK;
		player->Set_playstate(Player_Idle);

		break;
	}
	case 1: {
		nextpos = QPoint(pos.x(), pos.y() - 1);

		p_massagedata.m_errorcode = Errorcode_OK;
		player->Set_playstate(Player_Idle);

		break;
	}
	case 2: {
		nextpos = QPoint(pos.x(), pos.y() + 1);

		p_massagedata.m_errorcode = Errorcode_OK;
		player->Set_playstate(Player_Idle);

		break;
	}
	case 3: {
		nextpos = QPoint(pos.x() - 1, pos.y());

		p_massagedata.m_errorcode = Errorcode_OK;
		player->Set_playstate(Player_Idle);

		break;
	}
	case 4: {
		nextpos = QPoint(pos.x() + 1, pos.y());

		p_massagedata.m_errorcode = Errorcode_OK;

		break;
	}
	case 5: {
		player->Set_playstate(Player_Idle);
		p_massagedata.m_errorcode = Errorcode_OK;

		return;
	}

	default: {
		p_massagedata.m_errorcode = Errorcode_GAME_UNKNOWCOMMAND;
	}
		break;
	}
	if (Map.getSceneID(nextpos) != Impassable)
	{	//移動玩家
		Map.MoveUID(player->Get_Position(), nextpos, player->Get_UID());
		player->Set_Position(nextpos);
	}
	else
	{
		str += "<font color=\"red\">前方似乎無法通過</font>\n";
	}

	//生成怪物
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int random = std::rand() % 10;    
	if (random > 4 && Map.GetUIDList(player->Get_Position()).size() < 2)
	{
		std::srand(static_cast<unsigned int>(std::time(nullptr)+817)); //817為隨機質數
		random = std::rand() % 10;
		switch (Map.getSceneID(nextpos))
		{
		case Way: {
			if (random < 6)
				Spawn_Monsters(LV1_Slime, nextpos);			
			else if (random < 9)
				Spawn_Monsters(LV2_Wolf, nextpos);	
			else
				Spawn_Monsters(LV3_Goblin, nextpos);		
			break;
		}
			
		case Forest: {
			if (random < 6)
				Spawn_Monsters(LV4_ForestSlime, nextpos);
			else if (random < 9)
				Spawn_Monsters(LV5_ForestWolf, nextpos);
			else
				Spawn_Monsters(LV6_ForestGoblin, nextpos);
			break;
			break;
		}

		case Ruins: {
			if (random < 6)
				Spawn_Monsters(LV7_RuinSlime, nextpos);
			else if (random < 9)
				Spawn_Monsters(LV8_RuinWolf, nextpos);
			else
				Spawn_Monsters(LV9_RuinGoblin, nextpos);
			break;
			break;
		}
		case RuinsBoss: {
			Spawn_Monsters(LV10_Dragon, nextpos);
			break;
		}
		default:
			break;
		}
	}
	else
	{
		//不生成怪物
	}
	// 離開後怪物消失
	if (Map.GetUIDList(pos).size() < 2)
	{
		for each (int UID in Map.GetUIDList(pos))
		{
			if (UID >= MONSTER_UID_START && UID <= MONSTER_UID_END)
				Die_Role(UID);
		}
	}

}
void MUD_Engine::Observe(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand)
{
	if (Minorcommand > player->Get_SightRole().size())
	{
		if (player->Get_SightRole().size() == 0)
		{
			player->Set_playstate(Player_Idle);
			p_massagedata.m_errorcode = Errorcode_OK;
			return;
		}
		player->Set_playstate(Player_Observe);
		str += "沒有這個敵人\n";
		p_massagedata.m_errorcode = Errorcode_OK;
		return;
	}
	if (Minorcommand != 0)
	{
		int UID = player->Get_SightRole().at(Minorcommand-1);
		Role* role = Get_Role(UID);
		Monster* mon = dynamic_cast<Monster*>(role);
		if (mon)
		{
			player->Set_playstate(Player_Observe);
			str += "怪物名稱 : " + mon->Get_NAME() + "\n";
			str += "怪物血量 : " + QString::number(mon->Get_HP()) + "\n";
			str += "怪物等級 : " + QString::number(mon->Get_LV()) + "\n";

			p_massagedata.m_errorcode = Errorcode_OK;
		}
		else
		{
			p_massagedata.m_errorcode = Errorcode_GAME_UNKNOWCOMMAND;
		}
	}
	else
	{
		player->Set_playstate(Player_Idle);
		player->Clear_SightRole();

		p_massagedata.m_errorcode = Errorcode_OK;
	}
}
void MUD_Engine::Attack(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand)
{
	if (Minorcommand > player->Get_SightRole().size())
	{
		if (player->Get_SightRole().size() == 0)
		{
			player->Set_playstate(Player_Idle);
			p_massagedata.m_errorcode = Errorcode_OK;
			return;
		}

		player->Set_playstate(Player_Attack);
		str += "沒有這個敵人\n";
		p_massagedata.m_errorcode = Errorcode_OK;
		return;
	}
	if (Minorcommand != 0)
	{
		player->Set_BattleState(Battle_Attack);
		player->Set_playstate(Player_Battle);
		int mon_UID = player->Get_SightRole().at(Minorcommand - 1);
		Spawn_BattleRoom(player->Get_UID(), mon_UID);
		p_massagedata.m_errorcode = Errorcode_OK;
	}
	else
	{
		player->Set_playstate(Player_Idle);
		player->Clear_SightRole();
		p_massagedata.m_errorcode = Errorcode_OK;
	}
}
void MUD_Engine::Backpack(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand)
{
	switch (Minorcommand)
	{
	case 0: {
		player->Set_playstate(Player_Idle);
		p_massagedata.m_errorcode = Errorcode_OK;
		break;
	}
	case 1: {
		Show_Backpack(player, str);
		player->Set_playstate(Player_Backpack);
		p_massagedata.m_errorcode = Errorcode_OK;
		break;
	}
	case 2: {
		Show_Equipment(player, str);
		player->Set_playstate(Player_Backpack);
		p_massagedata.m_errorcode = Errorcode_OK;

		break;
	}
	case 3: {
		player->Set_playstate(Player_UseItem);
		p_massagedata.m_errorcode = Errorcode_OK;
		break;
	}
	case 4: {
		player->Set_playstate(Player_DropItem);
		p_massagedata.m_errorcode = Errorcode_OK;
		break;
	}
	default: {
		p_massagedata.m_errorcode = Errorcode_GAME_UNKNOWCOMMAND;
	}
		   break;
	}
}
void MUD_Engine::UseItem(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand)
{
	if (Minorcommand > player->Backpack.size())
	{
		if (player->Backpack.size() == 0)
		{
			player->Set_playstate(Player_Idle);
			p_massagedata.m_errorcode = Errorcode_OK;
			return;
		}
		player->Set_playstate(Player_UseItem);
		str += "沒有這個物品\n";
		p_massagedata.m_errorcode = Errorcode_OK;
		return;
	}
	if (Minorcommand != 0)
	{
		int itemid = player->Backpack.at(Minorcommand - 1);

		if (itemid >= EQUIPMENT_UID_START && itemid <= EQUIPMENT_UID_END)
		{
			//使用裝備
			Item_Equipment EQ;
			EQ_Table.Get_Equipment(static_cast<Item_EquipmentID>(itemid), EQ);
			Item_EquipmentParts part = EQ.Get_Part();
			Item_Equipment old_EQ;
			EQ_Table.Get_Equipment(static_cast<Item_EquipmentID>(player->Get_EQ(part)), old_EQ);
			str += " 脫下了 " + old_EQ.Get_NAME() + "\n";
			player->Backpack_Put(old_EQ.Get_ItemID(), str);
			str += old_EQ.Get_NAME() + "\n"; //接續Backpack_Put文字
			player->Set_EQ(part, Eq_Null);

			str += " 穿戴了 " + EQ.Get_NAME() + "\n";
			player->Set_EQ(part, static_cast<Item_EquipmentID>(EQ.Get_ItemID()));
			player->Backpack_Remove(Minorcommand - 1);

			player->Set_playstate(Player_Backpack);
			player->Clear_SightRole();
			p_massagedata.m_errorcode = Errorcode_OK;

		}
		else if (itemid >= POTION_UID_START && itemid <= POTION_UID_END)
		{
			//使用藥水
			
			Item_Potion Pot;
			Pot_Table.Get_Potion(static_cast<Item_PotionID>(itemid), Pot);
			str += " 使用了 "+ Pot.Get_NAME() + "\n";
			player->Backpack_Remove(Minorcommand - 1);
			switch (Pot.Get_Effect())
			{
			case PotionEffect_heal:
			{
				player->beHealingHP(Pot.Get_Value(), str);
				break;
			}
			//case PotionEffect_hurt:
			//{
			//	break;
			//}
			default:
				break;
			}
			player->Set_playstate(Player_Backpack);
			player->Clear_SightRole();
			p_massagedata.m_errorcode = Errorcode_OK;
		}
	}
	else
	{
		player->Set_playstate(Player_Backpack);
		player->Clear_SightRole();
		p_massagedata.m_errorcode = Errorcode_OK;
	}
}
void MUD_Engine::DropItem(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand)
{
	if (Minorcommand > player->Backpack.size())
	{
		if (player->Backpack.size() == 0)
		{
			player->Set_playstate(Player_Idle);
			p_massagedata.m_errorcode = Errorcode_OK;
			return;
		}

		player->Set_playstate(Player_DropItem);
		str += "沒有這個物品\n";
		p_massagedata.m_errorcode = Errorcode_OK;
		return;
	}

	if (Minorcommand != 0)
	{
		int itemid = player->Backpack.at(Minorcommand - 1);

		if (itemid >= EQUIPMENT_UID_START && itemid <= EQUIPMENT_UID_END)
		{
			Item_Equipment EQ;
			EQ_Table.Get_Equipment(static_cast<Item_EquipmentID>(itemid), EQ);
			if (player->Backpack_Remove(Minorcommand - 1))
				str += " 丟棄了 " + EQ.Get_NAME() + "\n";
			else
				str += " 移除失敗\n";
		}
		else if (itemid >= POTION_UID_START && itemid <= POTION_UID_END)
		{
			Item_Potion Pot;
			Pot_Table.Get_Potion(static_cast<Item_PotionID>(itemid), Pot);
			if(player->Backpack_Remove(Minorcommand - 1))
				str += " 丟棄了 " + Pot.Get_NAME() + "\n";
			else
				str += " 移除失敗\n";

		}
		p_massagedata.m_errorcode = Errorcode_OK;

	}
	else
	{
		player->Set_playstate(Player_Backpack);
		player->Clear_SightRole();
		p_massagedata.m_errorcode = Errorcode_OK;
	}
}
void MUD_Engine::Store(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand)
{
	if (Minorcommand > player->Get_SightRole().size())
	{
		if (player->Get_SightRole().size() == 0)
		{
			player->Set_playstate(Player_Idle);
			p_massagedata.m_errorcode = Errorcode_OK;
			return;
		}

		player->Set_playstate(Player_GoStore);
		str += "沒有這個商店\n";
		p_massagedata.m_errorcode = Errorcode_OK;
		return;
	}
	if (Minorcommand != 0)
	{
		StoreID storeid = static_cast<StoreID>(player->Get_SightRole().at(Minorcommand - 1));
		switch (storeid)
		{
		case Store_Weapon:
			player->Clear_SightRole();
			player->Add_SightRole(Newbie_Helmet);
			player->Add_SightRole(Iron_Helmet);
			player->Set_playstate(Player_Shopping);
			p_massagedata.m_errorcode = Errorcode_OK;


			break;
		case Store_Armor:
			player->Clear_SightRole();
			player->Add_SightRole(Newbie_Armor);
			player->Add_SightRole(Newbie_Shoe);
			player->Add_SightRole(Newbie_Sword);
			player->Add_SightRole(Iron_Armor);
			player->Add_SightRole(Iron_Shoe);
			player->Add_SightRole(Iron_Sword);
			player->Set_playstate(Player_Shopping);
			p_massagedata.m_errorcode = Errorcode_OK;


			break;
		case Store_Potion:
			player->Clear_SightRole();
			player->Add_SightRole(S_Healing_Potion);
			player->Add_SightRole(M_Healing_Potion);
			player->Set_playstate(Player_Shopping);
			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		case Store_Sell:
			player->Set_playstate(Player_Selling);
			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		default:
			p_massagedata.m_errorcode = Errorcode_GAME_UNKNOWCOMMAND;
			break;
		}

	}
	else
	{
		player->Set_playstate(Player_Idle);
		player->Clear_SightRole();
		p_massagedata.m_errorcode = Errorcode_OK;
	}
}
void MUD_Engine::Shopping(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand)
{
	if (Minorcommand > player->Get_SightRole().size())
	{
		if (player->Get_SightRole().size() == 0)
		{
			player->Set_playstate(Player_Idle);
			p_massagedata.m_errorcode = Errorcode_OK;
			return;
		}

		player->Set_playstate(Player_Shopping);
		str += "沒有這個商品\n";
		p_massagedata.m_errorcode = Errorcode_OK;
		return;
	}
	if (Minorcommand != 0)
	{
		int itemid = player->Get_SightRole().at(Minorcommand - 1);
		Buy_Item(itemid, player, str);
		player->Clear_SightRole();
		player->Set_playstate(Player_GoStore);
		p_massagedata.m_errorcode = Errorcode_OK;


	}
	else
	{
		player->Set_playstate(Player_Idle);
		player->Clear_SightRole();
		p_massagedata.m_errorcode = Errorcode_OK;
	}
}
void MUD_Engine::Selling(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand)
{
	if (Minorcommand > player->Backpack.size())
	{
		if (player->Backpack.size() == 0)
		{
			player->Set_playstate(Player_Idle);
			p_massagedata.m_errorcode = Errorcode_OK;
			return;
		}

		player->Set_playstate(Player_Selling);
		str += "沒有這個物品\n";
		p_massagedata.m_errorcode = Errorcode_OK;
		return;
	}

	if (Minorcommand != 0)
	{
		int itemid = player->Backpack.at(Minorcommand - 1);
		Sell_Item(Minorcommand - 1, player, str);
		p_massagedata.m_errorcode = Errorcode_OK;

	}
	else
	{
		player->Set_playstate(Player_GoStore);
		player->Clear_SightRole();
		p_massagedata.m_errorcode = Errorcode_OK;
	}
}
void MUD_Engine::Battling(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand)
{
	switch (player->Get_BattleState())
	{
	case Battle_Attack:
		switch (Minorcommand)
		{
		case 1: {
			player->Set_BattleState(Battle_Run);
			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}
		default: {
			//str += "錯誤指令\n";
			p_massagedata.m_errorcode = Errorcode_OK;
		}
			   break;
		}		break;
	case Battle_Item:
		break;
	case Battle_Run:
	{
		switch (Minorcommand)
		{
		case 1: {
			player->Set_BattleState(Battle_Attack);
			p_massagedata.m_errorcode = Errorcode_OK;
			break;
		}
		default: {
			//str += "錯誤指令\n";
			p_massagedata.m_errorcode = Errorcode_OK;
		}
			   break;
		}
		break;
	}
	default:
		break;
	}

}


// Item相關文字說明,因需配合串表,故無法直接寫在Player
void MUD_Engine::Show_Path(QPoint pos, QString& str)
{
	str += "可以通往";
	if (Map.getSceneID(QPoint(pos.x(), pos.y() + 1)))
		str += "↓";
	if (Map.getSceneID(QPoint(pos.x(), pos.y() - 1)))
		str += "↑";
	if (Map.getSceneID(QPoint(pos.x() - 1, pos.y())))
		str += "←";
	if (Map.getSceneID(QPoint(pos.x() + 1, pos.y())))
		str += "→";
	str += "\n";
}
void MUD_Engine::Show_Player(Player* m_player, QString& str)
{
	str += m_player->Get_NAME() + " 角色資訊:\n";
	str += "NAME  : "	+ m_player->Get_NAME() + "\n";
	str += "HP    : "	+ QString::number(m_player->Get_HP())	+ "/" + QString::number(m_player->total_HPMAX) + "\n";
	str += "MP    : "	+ QString::number(m_player->Get_MP())	+ "/" + QString::number(m_player->total_MPMAX) + "\n";
	str += "ATK   : "	+ QString::number(m_player->total_ATK)	+ "\n";
	str += "DEF   : "	+ QString::number(m_player->total_DEF)	+ "\n";
	str += "LV    : "	+ QString::number(m_player->Get_LV())	+ "\n";
	str += "EXP   : "	+ QString::number(m_player->Get_EXP())	+ "\n";
	str += "Money : "	+ QString::number(m_player->Get_Money())+ "\n";
}
void MUD_Engine::Show_Equipment(Player * m_player, QString & str)
{
	str += m_player->Get_NAME() + " 使用中裝備:\n";

	Item_Equipment EQ;
	EQ_Table.Get_Equipment(m_player->Eqs_Using[Part_Weapon],EQ);
	if (!EQ.Get_NAME().isEmpty()) {
		str += "手上武器 : " + EQ.Get_NAME() + "\n";
		EQ.Show(str);
	}
	else {
		str += "手上武器 : 無穿戴\n";
	}

	EQ_Table.Get_Equipment(m_player->Eqs_Using[Part_Helmet], EQ);
	if (!EQ.Get_NAME().isEmpty()) {
		str += "頭部裝備 : " + EQ.Get_NAME() + "\n";
		EQ.Show(str);
	}
	else {
		str += "頭部裝備 : 無穿戴\n";
	}

	EQ_Table.Get_Equipment(m_player->Eqs_Using[Part_Armor], EQ);
	if (!EQ.Get_NAME().isEmpty()) {
		str += "身體裝備 : " + EQ.Get_NAME() + "\n";
		EQ.Show(str);
	}
	else {
		str += "身體裝備 : 無穿戴\n";
	}

	EQ_Table.Get_Equipment(m_player->Eqs_Using[Part_Shoe], EQ);
	if (!EQ.Get_NAME().isEmpty()) {
		str += "腿部裝備 : " + EQ.Get_NAME() + "\n";
		EQ.Show(str);
	}
	else {
		str += "腿部裝備 : 無穿戴\n";
	}
}
void MUD_Engine::Show_Backpack(Player* m_player, QString& str) 
{
	str += m_player->Get_NAME() + " 背包:\n";
	if (m_player->Backpack.size() == 0)
	{
		str += "空的\n";
		return;
	}
	int i = 1;
	for each (int itemid in m_player->Backpack)
	{
		if (itemid >= EQUIPMENT_UID_START && itemid <= EQUIPMENT_UID_END)
		{
			Item_Equipment EQ;
			EQ_Table.Get_Equipment(static_cast<Item_EquipmentID>(itemid), EQ);
			str += QString::number(i) +".名稱 : " + EQ.Get_NAME() + "\n";

		}
		else if(itemid >= POTION_UID_START && itemid <= POTION_UID_END)
		{
			Item_Potion Pot;
			Pot_Table.Get_Potion(static_cast<Item_PotionID>(itemid), Pot);
			str += QString::number(i) + ".名稱 : " + Pot.Get_NAME() + "\n";

		}
		++i;
	}

}
void MUD_Engine::Buy_Item(int ItemID, Player* m_player, QString& str)
{
	if (ItemID >= EQUIPMENT_UID_START && ItemID <= EQUIPMENT_UID_END)
	{
		Item_Equipment EQ;
		EQ_Table.Get_Equipment(static_cast<Item_EquipmentID>(ItemID), EQ);
		if (m_player->Cost_Money(EQ.Get_Money(), str))
		{
			//str += "購買 : "+ EQ.Get_NAME() +"\n";
			m_player->Backpack_Put(EQ.Get_ItemID(), str);
			str += EQ.Get_NAME() + "\n"; //接續Backpack_Put文字
		}
	}
	else if (ItemID >= POTION_UID_START && ItemID <= POTION_UID_END)
	{
		Item_Potion Pot;
		Pot_Table.Get_Potion(static_cast<Item_PotionID>(ItemID), Pot);
		if (m_player->Cost_Money(Pot.Get_Money(), str))
		{
			//str += "購買 : " + Pot.Get_NAME() + "\n";
			m_player->Backpack_Put(Pot.Get_ItemID(), str);
			str += Pot.Get_NAME() + "\n"; //接續Backpack_Put文字

		}
	}
}
void MUD_Engine::Sell_Item(int index, Player * m_player, QString & str)
{
	int itemid = m_player->Backpack.at(index);
	if (itemid >= EQUIPMENT_UID_START && itemid <= EQUIPMENT_UID_END)
	{
		Item_Equipment EQ;
		EQ_Table.Get_Equipment(static_cast<Item_EquipmentID>(itemid), EQ);
		if (m_player->Backpack_Remove(index))
		{
			str += " 販賣了 " + EQ.Get_NAME() + "\n";
			m_player->Add_Money(EQ.Get_Money() / 2, str);
		}
		else
		{
			str += " 販賣失敗\n";
		}
		
	}
	else if (itemid >= POTION_UID_START && itemid <= POTION_UID_END)
	{
		Item_Potion Pot;
		Pot_Table.Get_Potion(static_cast<Item_PotionID>(itemid), Pot);
		if (m_player->Backpack_Remove(index))
		{
			str += " 販賣了 " + Pot.Get_NAME() + "\n";
			m_player->Add_Money(Pot.Get_Money() / 2, str);
		}
		else
		{
			str += " 販賣失敗\n";
		}
	}
}