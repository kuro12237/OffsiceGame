#pragma once
#include"ModelManager.h"
#include"ViewProjection.h"
#include"Model.h"
#include"FileLoader.h"
#include"MapData.h"

#define MAP_MAX_X 30
#define MAP_MAX_Y 30
#define MAP_MAX_Z 2

class MapManager
{
public:
	MapManager() {};
	~MapManager() {};

	static MapManager* GetInstance();

	static void Initialize();

	static void Update();

	static void Draw(ViewProjection view);

	static void SetNextMaptip(uint32_t next);

	static uint32_t GetNowstageMapTip() { return MapManager::GetInstance()->nowStage_; };

private:

	static void FileLoad(string name);

	static bool ChackNowMapTip();

	uint32_t nowStage_ = 1;
	uint32_t prevSatge_ = 0;

	vector<vector<vector<Block_param>>>block_ = {};
	/// <summary>
	/// zyx
	/// </summary>
	vector<vector<vector<uint32_t>>>nowMapData_ = {};

	/// <summary>
	/// 初期化事故防止
	/// </summary>
	bool InitializeLock_ = false;

	string FilePath = "Resources/MapData/";

	map<string, unique_ptr<MapData>>mapDatas_;

	uint32_t ModelHandle_ = 0;

	bool flag = false;

	string nowFilename{};
};