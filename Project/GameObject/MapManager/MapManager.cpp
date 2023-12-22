#include "MapManager.h"

MapManager* MapManager::GetInstance()
{
    static MapManager instance;
    return &instance;
}

void MapManager::Initialize()
{
	if (!MapManager::GetInstance()->InitializeLock_)
	{
		FileLoad("Stage1");
		FileLoad("Stage2");

		MapManager::GetInstance()->nowStage_ = 1;
		MapManager::GetInstance()->ModelHandle_ = ModelManager::LoadObjectFile("TestWoodBlock");

		MapManager::GetInstance()->block_.resize(MAP_MAX_Z);
		for (size_t z = 0; z < MAP_MAX_Z; z++)
		{
			MapManager::GetInstance()->block_[z].resize(MAP_MAX_Y);
			for (size_t y = 0; y < MAP_MAX_Y; y++)
			{
				MapManager::GetInstance()->block_[z][y].resize(MAP_MAX_X);
				for (size_t x = 0; x < MAP_MAX_X; x++)
				{
					MapManager::GetInstance()->block_[z][y][x].model = make_unique<Game3dObject>();
					MapManager::GetInstance()->block_[z][y][x].model->UseLight(true);
					MapManager::GetInstance()->block_[z][y][x].model->Create();
					MapManager::GetInstance()->block_[z][y][x].model->SetModel(MapManager::GetInstance()->ModelHandle_);
					MapManager::GetInstance()->block_[z][y][x].worldTransform.Initialize();
					MapManager::GetInstance()->block_[z][y][x].worldTransform.scale = { 0.5f,0.5f,0.5f };
					MapManager::GetInstance()->block_[z][y][x].worldTransform.translate.x = static_cast<float>(x);
					MapManager::GetInstance()->block_[z][y][x].worldTransform.translate.y = static_cast<float>(MAP_MAX_Y - y);
					MapManager::GetInstance()->block_[z][y][x].worldTransform.translate.z = static_cast<float>(z);
				}
			}
		}
	}
}

void MapManager::Update()
{
    //前フレームと今のフレームのマップ番号が違うときにマップデータを切り替える
    if (ChackNowMapTip())
    {
		for (const auto& [key, s] : MapManager::GetInstance()->mapDatas_)
		{
			if (s.get()->GetStageNumber() == MapManager::GetInstance()->nowStage_)
			{
				MapManager::GetInstance()->nowMapData_ = s.get()->GetMapData();
				MapManager::GetInstance()->FilePath = key;
			}
		}
		MapManager::GetInstance()->prevSatge_ = MapManager::GetInstance()->nowStage_;
    }

	//world更新
	for (uint32_t z = 0; z < MapManager::GetInstance()->nowMapData_.size(); z++)
	{
		for (int y = 0; y < MapManager::GetInstance()->nowMapData_[z].size(); y++)
		{
			for (int x = 0; x < MapManager::GetInstance()->nowMapData_[z][y].size(); x++)
			{
			
				MapManager::GetInstance()->block_[z][y][x].worldTransform.UpdateMatrix();
				
			}
		}
	}
}

void MapManager::Draw(ViewProjection view)
{
	for (size_t z = 0; z < MapManager::GetInstance()->nowMapData_.size(); z++)
	{
		for (size_t y = 0; y < MapManager::GetInstance()->nowMapData_[z].size(); y++)
		{
			for (size_t x = 0; x < MapManager::GetInstance()->nowMapData_[z][y].size(); x++)
			{
				if (MapManager::GetInstance()->nowMapData_[z][y][x] == 1)
				{
					MapManager::GetInstance()->block_[z][y][x].model->Draw(MapManager::GetInstance()->block_[z][y][x].worldTransform, view);
				}
			}
		}
	}
}

void MapManager::SetNextMaptip(uint32_t next)
{
    MapManager::GetInstance()->prevSatge_ = MapManager::GetInstance()->nowStage_;
    MapManager::GetInstance()->nowStage_ = next;
}

void MapManager::FileLoad(string name)
{
    string FileName = MapManager::GetInstance()->FilePath + name +".csv";

    stringstream file = FileLoader::CSVLoadFile(FileName);

	string line;
	uint32_t stageNumber = 0;
	uint32_t ZNumber = 0;
	uint32_t ZNumNumber = 0;
	vector<vector<vector<uint32_t>>>maptip{};
	int mapYCount = -1;
	
	while (getline(file, line))
	{
		istringstream line_stream(line);
		string word;
		getline(line_stream, word, ',');

		if (word.find("//") == 0)
		{
			continue;
		}

		if (word.find("StageNumber") == 0)
		{
			getline(line_stream, word, ',');
			stageNumber = (uint32_t)std::atof(word.c_str());
		
		}

		if (word.find("ZNumber") == 0)
		{
			getline(line_stream, word, ',');
			ZNumber = (uint32_t)std::atof(word.c_str());
			maptip.resize(ZNumber+1);
			mapYCount = -1;
			ZNumNumber++;
		}

		if (word.find("MapData" ) == 0)
		{
			//Y++
			mapYCount++;
			maptip[ZNumber].resize(mapYCount+1);
		
			size_t mapCount = (line.size() - string("MapData").size()) / 2;
			maptip[ZNumber][mapYCount].resize(mapCount);

			for (int mapXCount = 0; mapXCount < mapCount; mapXCount++)
			{
				getline(line_stream, word, ',');
				uint32_t xNumber = (uint32_t)atof(word.c_str());
				maptip[ZNumber][mapYCount][mapXCount] = xNumber;
			
			}
		}
	
	}

	MapManager::GetInstance()->mapDatas_[FileName] = make_unique<MapData>(stageNumber, ZNumNumber, maptip);
	maptip.clear();
}


bool MapManager::ChackNowMapTip()
{
    if (MapManager::GetInstance()->prevSatge_ != MapManager::GetInstance()->nowStage_)
    {
        return true;
    }
    return false;
}
