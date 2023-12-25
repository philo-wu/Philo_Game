#pragma once

#include <QString>
#include <QList>

class Monster;
enum SceneID
{
	Impassable ,
	Village ,
	Way ,
	Forest ,
	Ruins ,
	RuinsBoss 
};
enum StoreID
{
	Store_Weapon,
	Store_Armor ,
	Store_Potion
};

//以下為將每張地圖視為單獨個體來實做

class Scene
{
public:
	Scene(SceneID p_Scene_ID)
		: Scene_ID(p_Scene_ID)
	{

	}
	SceneID Scene_ID;
};

class SafeScene : public Scene
{
public:
	SafeScene(SceneID p_Scene_ID)
		: Scene(p_Scene_ID)
	{
	}
private:
	QList<StoreID> Stores;
};

class DangerScene : public Scene
{
public:
	DangerScene(SceneID p_Scene_ID)
		: Scene(p_Scene_ID)
	{
	}
private:
	QList<Monster> Monsters;
};