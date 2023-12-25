#include "MUD_Engine.h"
MUD_Engine::MUD_Engine()
{
	EXP_Table.parseTable("/data/LV_EXP.json");
	Mon_Table.parseTable("/data/Monster.json");
	UID_Table.parseTable("/data/UID.json");
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


void MUD_Engine::Scenes_Info(MassageData& p_massagedata,Player* player, int& Minorcommand)
{
	QString str;
	switch (player->Get_playstate())
	{
	case Player_Idle: {
		switch (Map.getSceneID(player->Get_Position()))
		{
		case Impassable: {
			str = "不應該位於當前地點\n";
			break;
		}
		case Village: {
			str += "==小鎮==\n";
			str += "一個寧靜的小鎮,有許多房子和人\n";
			break;
		}
		case Way: {
			str += "==道路==\n";
			str += "一個平坦的道路,旁邊似乎有甚麼東西\n";
			break;
		}
		case Forest: {
			str += "==森林==\n";
			str += "一個幽暗的森林,看不到太遠的地方\n";
			break;
		}
		case Ruins: {
			str += "==廢墟==\n";
			str += "一個殘破的廢墟,之前有許多房子和人\n";
			break;
		}
		case RuinsBoss: {
			str += "==廢墟Boss==\n";
			str += "前方就是惡龍所在的地方,準備好挑戰了嗎\n";
			break;
		}
		default:
			p_massagedata.m_errorcode = Errorcode_GAME_UNKNOWCOMMAND;
			break;
		}
		if (Map.getSceneID(player->Get_Position()) == Impassable)
		{

		}
		else if (Map.getSceneID(player->Get_Position()) == Village)
		{
			//安全區域
			str += "1.移動\n";
			str += "2.使用物品\n";
			str += "3.使用裝備\n";
			str += "4.去商店\n";
		}
		else if (Map.getSceneID(player->Get_Position())!= Village)
		{
			//危險區域
			if (Map.GetUIDList(player->Get_Position()).size()>1)
				str += "!!!這裡似乎有東西在動!!!\n";
			str += "1.移動\n";
			str += "2.觀察\n";
			str += "3.攻擊\n";
			str += "4.使用物品\n";
			str += "5.使用裝備\n";
		}
		break;
	}
	case Player_Move: {
		str = "想要往哪裡移動\n";
		str += "0.取消\n";
		str += "1.上\n";
		str += "2.下\n";
		str += "3.左\n";
		str += "4.右\n";
		break;
	}
	case Player_Observe: {
		str = "想要觀察誰\n";
		str += "0.取消\n";
		int i = 1;
		for each (int UID in Map.GetUIDList(player->Get_Position()))
		{
			if (UID < MONSTER_UID_START || UID >> MONSTER_UID_START)
				continue;
			Role* role = Get_Role(UID);
			Monster * mon = dynamic_cast<Monster*>(role);
			if (mon)
			{
				str += QString::number(i++) + "." + mon->Get_NAME() + "\n";
				player->Add_SightRole(UID);
			}
		}
		break;
	}
	case Player_Attack: {
		str = "想要攻擊誰\n";
		str += "0.取消\n";
		int i = 1;
		for each (int UID in Map.GetUIDList(player->Get_Position()))
		{
			if (UID < MONSTER_UID_START || UID >> MONSTER_UID_START)
				continue;
			Role* role = Get_Role(UID);
			Monster* mon = dynamic_cast<Monster*>(role);
			if (mon)
			{
				str += QString::number(i++) + "." + mon->Get_NAME() + "\n";
				player->Add_SightRole(UID);
			}
		}
		break;
	}
	case Player_UseItem: {
		str = "想要使用甚麼\n";
		str += "test\n";
		str += "0.取消\n";
		str += "1.小紅藥\n";
		str += "2.小紅藥\n";
		str += "3.小紅藥\n";
		str += "4.取消\n";
		break;
	}
	case Player_UseEQ: {
		str = "想要穿戴甚麼\n";
		str += "test\n";
		str += "0.取消\n";
		str += "1.森林頭盔\n";
		str += "2.銅劍\n";
		str += "3.廢墟護甲\n";
		break;
	}
	case Player_Store: {
		str = "要去哪間商店\n";
		str += "test\n";
		str += "0.取消\n";
		str += "1.武器店\n";
		str += "2.防具店\n";
		str += "3.藥水店\n";


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
	//str += "歡迎來到勇者鬥惡龍\n";
	//str += "qwer";

	switch (player->Get_playstate())
	{
	case Player_Idle: {
		idle(p_massagedata, str, player, Minorcommand);
		break;
	}
	case Player_Move: {
		str += "==移動==\n";
		Move(p_massagedata, str, player, Minorcommand);
		break;
	}
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
	case Player_UseItem: {
		str += "==使用物品==\n";
		UseItem(p_massagedata, str, player, Minorcommand);
		break;
	}
	case Player_UseEQ: {
		str += "==使用裝備==\n";
		UseEQ(p_massagedata, str, player, Minorcommand);
		break;
	}
	case Player_Store: {
		str += "==商店==\n";
		Store(p_massagedata, str, player, Minorcommand);
		break;
	}
	default:
		p_massagedata.m_errorcode = Errorcode_GAME_UNKNOWCOMMAND;
		break;
	}
	p_massagedata.m_Data["GameText"] = str;
	p_massagedata.m_Time = QDateTime::currentDateTime();
}

		
void MUD_Engine::Spawn_Monsters(MonsterID MID, QPoint pos)
{
	Monster* Mons = new Monster;
	Mons->Set_Position(pos);
	Mons->Set_UID(UID_Table.GetMonsterUID());

	switch (MID)
	{
	case LV1_Slime:{
		int LV = 1;
		Mons->Set_NAME("史萊姆");
		Mons->Set_LV(LV);
		Mons->Set_HP(5);
		Mons->Set_MP(0);
		Mons->Set_ATK(3);
		Mons->Set_DEF(0);
		Mons->Set_EXP(Mon_Table.GetEXP(LV));
		Mons->Set_Money(Mon_Table.GetMoney(LV));
	}
		break;
	case LV2_Wolf: {
		int LV = 2;
		Mons->Set_NAME("狼");
		Mons->Set_LV(LV);
		Mons->Set_HP(10);
		Mons->Set_MP(0);
		Mons->Set_ATK(3);
		Mons->Set_DEF(1);
		Mons->Set_EXP(Mon_Table.GetEXP(LV));
		Mons->Set_Money(Mon_Table.GetMoney(LV));

	}
		break;
	case LV3_Goblin: {
		int LV = 3;
		Mons->Set_NAME("哥布林");
		Mons->Set_LV(LV);
		Mons->Set_HP(15);
		Mons->Set_MP(0);
		Mons->Set_ATK(4);
		Mons->Set_DEF(1);
		Mons->Set_EXP(Mon_Table.GetEXP(LV));
		Mons->Set_Money(Mon_Table.GetMoney(LV));

	}
		break;
	case LV4_ForestSlime: {
		int LV = 4;
		Mons->Set_NAME("森林史萊姆");
		Mons->Set_LV(LV);
		Mons->Set_HP(20);
		Mons->Set_MP(0);
		Mons->Set_ATK(4);
		Mons->Set_DEF(0);
		Mons->Set_EXP(Mon_Table.GetEXP(LV));
		Mons->Set_Money(Mon_Table.GetMoney(LV));

	}
		break;
	case LV5_ForestWolf: {
		int LV = 5;
		Mons->Set_NAME("森林狼");
		Mons->Set_LV(LV);
		Mons->Set_HP(25);
		Mons->Set_MP(0);
		Mons->Set_ATK(4);
		Mons->Set_DEF(1);
		Mons->Set_EXP(Mon_Table.GetEXP(LV));
		Mons->Set_Money(Mon_Table.GetMoney(LV));

	}
		break;
	case LV6_ForestGoblin: {
		int LV = 6;
		Mons->Set_NAME("森林哥布林");
		Mons->Set_LV(LV);
		Mons->Set_HP(30);
		Mons->Set_MP(0);
		Mons->Set_ATK(5);
		Mons->Set_DEF(1);
		Mons->Set_EXP(Mon_Table.GetEXP(LV));
		Mons->Set_Money(Mon_Table.GetMoney(LV));

	}
		break;
	case LV7_RuinSlime: {
		int LV = 7;
		Mons->Set_NAME("廢墟史萊姆");
		Mons->Set_LV(LV);
		Mons->Set_HP(50);
		Mons->Set_MP(0);
		Mons->Set_ATK(7);
		Mons->Set_DEF(0);
		Mons->Set_EXP(Mon_Table.GetEXP(LV));
		Mons->Set_Money(Mon_Table.GetMoney(LV));

	}
		break;
	case LV8_RuinWolf: {
		int LV = 8;
		Mons->Set_NAME("廢墟狼");
		Mons->Set_LV(LV);
		Mons->Set_HP(60);
		Mons->Set_MP(0);
		Mons->Set_ATK(8);
		Mons->Set_DEF(2);
		Mons->Set_EXP(Mon_Table.GetEXP(LV));
		Mons->Set_Money(Mon_Table.GetMoney(LV));

	}
		break;
	case LV9_RuinGoblin: {
		int LV = 9;
		Mons->Set_NAME("廢墟哥布林");
		Mons->Set_LV(LV);
		Mons->Set_HP(70);
		Mons->Set_MP(0);
		Mons->Set_ATK(8);
		Mons->Set_DEF(3);
		Mons->Set_EXP(Mon_Table.GetEXP(LV));
		Mons->Set_Money(Mon_Table.GetMoney(LV));

	}
		break;
	case LV10_Dragon: {
		int LV = 10;
		Mons->Set_NAME("惡龍");
		Mons->Set_LV(LV);
		Mons->Set_HP(200);
		Mons->Set_MP(0);
		Mons->Set_ATK(15);
		Mons->Set_DEF(12);
		Mons->Set_EXP(Mon_Table.GetEXP(LV));
		Mons->Set_Money(Mon_Table.GetMoney(LV));
	}
		break;
	default:
		break;
	}

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
	switch (Minorcommand)
	{
	case 0: {
		player->Set_playstate(Player_Idle);
		p_massagedata.m_errorcode = Errorcode_OK;
		break;
	}
	case 1: {
		player->Set_playstate(Player_Move);
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
		player->Set_playstate(Player_UseItem);

		p_massagedata.m_errorcode = Errorcode_OK;
		break;
	}
	case 5: {
		player->Set_playstate(Player_UseEQ);

		p_massagedata.m_errorcode = Errorcode_OK;
		break;
	}
	case 6: {
		player->Set_playstate(Player_Store);

		p_massagedata.m_errorcode = Errorcode_OK;
		break;
	}
	case 11: {
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
void MUD_Engine::Move(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand)
{
	QPoint pos = player->Get_Position();
	QPoint nextpos;

	switch (Minorcommand)
	{
	case 0: {
		p_massagedata.m_errorcode = Errorcode_OK;
		break;
	}
	case 1: {
		nextpos = QPoint(pos.x(), pos.y() - 1);

		p_massagedata.m_errorcode = Errorcode_OK;

		break;
	}
	case 2: {
		nextpos = QPoint(pos.x(), pos.y() + 1);

		p_massagedata.m_errorcode = Errorcode_OK;

		break;
	}
	case 3: {
		nextpos = QPoint(pos.x() - 1, pos.y());

		p_massagedata.m_errorcode = Errorcode_OK;

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
		str += "前方似乎無法通過 \n";

	//生成怪物
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int random = std::rand() % 10;    
	if (random > 4 && Map.GetUIDList(player->Get_Position()).size() < 2)
	{
		std::srand(static_cast<unsigned int>(std::time(nullptr)+717)); //17為隨機質數
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

	//QDebug() << ;
	player->Set_playstate(Player_Idle);
}
void MUD_Engine::Observe(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand)
{
	if (Minorcommand > player->Get_SightRole().size())
	{
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
	if (Minorcommand > player->Get_SightRole().size()-1)
	{
		player->Set_playstate(Player_Attack);
		str += "沒有這個敵人\n";
		p_massagedata.m_errorcode = Errorcode_OK;
		return;
	}
	if (Minorcommand != 0)
	{
		int UID = player->Get_SightRole().at(Minorcommand - 1);
		Role* role = Get_Role(UID);
		Monster* mon = dynamic_cast<Monster*>(role);
		if (mon)
		{


			player->Set_playstate(Player_Attack);

			player->Attack(mon, str);

			p_massagedata.m_errorcode = Errorcode_OK;
			if (mon->Get_HP() <= 0)
			{
				str += mon->Get_NAME() + " 死亡\n";
				//怪物死掉
				player->Add_EXP(mon->Get_EXP(), str);
				player->Add_Money(mon->Get_Money(), str);
				player->Check_LVUP(EXP_Table.GetEXP(player->Get_LV()), str);
			}
			else
			{
				mon->Attack(player, str);
			}
			if (mon->Get_HP() <= 0) //最後才刪除怪物
				Die_Role(mon->Get_UID());
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
void MUD_Engine::UseItem(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand)
{
	switch (Minorcommand)
	{
	case 0: {
		p_massagedata.m_errorcode = Errorcode_OK;
		break;
	}
	case 1: {
		p_massagedata.m_errorcode = Errorcode_OK;

		break;
	}
	case 2: {
		p_massagedata.m_errorcode = Errorcode_OK;

		break;
	}
	case 3: {
		p_massagedata.m_errorcode = Errorcode_OK;

		break;
	}
	case 4: {
		p_massagedata.m_errorcode = Errorcode_OK;

		break;
	}
	case 5: {
		p_massagedata.m_errorcode = Errorcode_OK;

		break;
	}

	default: {
		p_massagedata.m_errorcode = Errorcode_GAME_UNKNOWCOMMAND;
	}
		   break;
	}
	player->Set_playstate(Player_Idle);

}
void MUD_Engine::UseEQ(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand)
{
	switch (Minorcommand)
	{
	case 0: {
		p_massagedata.m_errorcode = Errorcode_OK;
		break;
	}
	case 1: {
		p_massagedata.m_errorcode = Errorcode_OK;

		break;
	}
	case 2: {
		p_massagedata.m_errorcode = Errorcode_OK;

		break;
	}
	case 3: {
		p_massagedata.m_errorcode = Errorcode_OK;

		break;
	}
	case 4: {
		p_massagedata.m_errorcode = Errorcode_OK;

		break;
	}
	case 5: {
		p_massagedata.m_errorcode = Errorcode_OK;

		break;
	}

	default: {
		p_massagedata.m_errorcode = Errorcode_GAME_UNKNOWCOMMAND;
	}
		   break;
	}
	player->Set_playstate(Player_Idle);

}
void MUD_Engine::Store(MassageData& p_massagedata, QString& str, Player* player, int Minorcommand)
{
	switch (Minorcommand)
	{
	case 0: {
		p_massagedata.m_errorcode = Errorcode_OK;
		break;
	}
	case 1: {
		p_massagedata.m_errorcode = Errorcode_OK;

		break;
	}
	case 2: {
		p_massagedata.m_errorcode = Errorcode_OK;

		break;
	}
	case 3: {
		p_massagedata.m_errorcode = Errorcode_OK;

		break;
	}
	case 4: {
		p_massagedata.m_errorcode = Errorcode_OK;

		break;
	}
	case 5: {
		p_massagedata.m_errorcode = Errorcode_OK;

		break;
	}

	default: {
		p_massagedata.m_errorcode = Errorcode_GAME_UNKNOWCOMMAND;
	}
		   break;
	}
	player->Set_playstate(Player_Idle);

}