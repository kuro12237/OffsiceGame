#include "MapObject.h"

MapObject::MapObject()
{

}

MapObject::~MapObject()
{
	block_.clear();
}

void MapObject::Initialize(vector<vector<vector<uint32_t>>> nowData)
{
	this->MapData_ = nowData;
	this->Zsize_ = uint32_t(nowData.size());
	this->Ysize_ = uint32_t(nowData[0].size());
	this->Xsize_ = uint32_t(nowData[0][0].size());

	modelHandle_ = ModelManager::LoadObjectFile("TestWoodBlock");

	block_.resize(Zsize_);
	for (size_t z = 0; z < Zsize_; z++)
	{
		block_[z].resize(Ysize_);

		for (size_t y = 0; y < Ysize_; y++)
		{
			block_[z][y].resize(Xsize_);

			for (size_t x = 0; x < Xsize_; x++)
			{
				block_[z][y][x].object = make_unique<Game3dObject>();
				block_[z][y][x].object->UseLight(true);
				block_[z][y][x].object->Create();
				block_[z][y][x].object->SetModel(modelHandle_);
				block_[z][y][x].worldTransform.Initialize();
				block_[z][y][x].worldTransform.scale = { 0.5f,0.5f,0.5f };
				block_[z][y][x].worldTransform.translate.x = static_cast<float>(x);
				block_[z][y][x].worldTransform.translate.y = static_cast<float>(Ysize_ - y);
				block_[z][y][x].worldTransform.translate.z = static_cast<float>(z);
			}
		}
	}

}

void MapObject::Update()
{
	for (uint32_t z = 0; z < Zsize_; z++)
	{
		for (uint32_t y = 0; y < Ysize_; y++)
		{
			for (uint32_t x = 0; x < Xsize_; x++)
			{
				block_[z][y][x].worldTransform.UpdateMatrix();
			}
		}
	}
}

void MapObject::Draw(ViewProjection view)
{
	for (uint32_t z = 0; z < Zsize_; z++)
	{
		for (uint32_t y = 0; y < Ysize_; y++)
		{
			for (uint32_t x = 0; x < Xsize_; x++)
			{
				block_[z][y][x].object->Draw(block_[z][y][x].worldTransform, view);
			}
		}
	}
}
