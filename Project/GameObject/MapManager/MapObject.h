#pragma once
#include"Game3dObject.h"



struct Block_param
{
	unique_ptr<Game3dObject>object = nullptr;
	WorldTransform worldTransform;
};
class MapObject
{
public:
	MapObject();
	~MapObject();


	void Initialize( vector<vector<vector<uint32_t>>> nowData);

	void Update();

	void Draw(ViewProjection view);

private:

	uint32_t modelHandle_ = 0;

	uint32_t Zsize_ = 0;
	uint32_t Ysize_ = 0;
	uint32_t Xsize_ = 0;

	vector<vector<vector<Block_param>>>block_ = {};
	vector<vector<vector<uint32_t>>>MapData_ = {};
};