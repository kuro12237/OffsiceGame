#pragma once
#include"Model.h"

struct Block_param
{
	unique_ptr<Model>model = nullptr;
	WorldTransform worldTransform;
};

class MapData
{
public:
	MapData(uint32_t StageNumber,uint32_t ZData,vector<vector<vector<uint32_t>>> data) {
		StageNumber_ = StageNumber; 
		ZData_ = ZData;
		mapData_ = data;
	};

	~MapData() {};


	uint32_t GetStageNumber() { return StageNumber_; }
	
	vector<vector<vector<uint32_t>>> GetMapData() { return mapData_; }

private:

	vector<vector<vector<uint32_t>>>mapData_ = {};
	uint32_t StageNumber_ = 0;
	uint32_t ZData_;
};