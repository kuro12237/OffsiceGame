#pragma once
#include"ModelManager.h"
#include"ViewProjection.h"
#include"Model.h"
#include"FileLoader.h"
#include"MapData.h"


class MapManager
{
public:
	MapManager() {};
	~MapManager() {};

	static MapManager* GetInstance();

	static void Initialize();

	static void Update();


	static void SetNextMaptip(uint32_t next);

	static uint32_t GetNowstageMapTip() { return MapManager::GetInstance()->nowStage_; };

	static 	vector<vector<vector<uint32_t>>> GetMapData() { return MapManager::GetInstance()->nowMapData_; }

private:

	static void FileLoad(string name);

	static bool ChackNowMapTip();

	uint32_t nowStage_ = 1;
	uint32_t prevSatge_ = 0;

	/// <summary>
	/// zyx
	/// </summary>
	vector<vector<vector<uint32_t>>>nowMapData_ = {};

	string FilePath = "Resources/MapData/";

	map<string, unique_ptr<MapData>>mapDatas_;

	uint32_t ModelHandle_ = 0;

	bool flag = false;
};