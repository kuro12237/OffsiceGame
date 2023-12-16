#include "MapManager.h"

MapManager* MapManager::GetInstance()
{
    static MapManager instance;
    return &instance;
}

void MapManager::Initialize()
{
    FileLoad("Stage1");
	//FileLoad("Stage2");

	MapManager::GetInstance()->nowStage_ = 1;
	
}

void MapManager::Update()
{
    //前フレームと今のフレームのマップ番号が違うときにマップデータを切り替える
    if (ChackNowMapTip())
    {
		for (const auto& [key, s] : MapManager::GetInstance()->mapDatas_)
		{
			key;
			if (s.get()->GetStageNumber() == MapManager::GetInstance()->nowStage_)
			{
				MapManager::GetInstance()->nowMapData_ = s.get()->GetMapData();
			}
		}
		MapManager::GetInstance()->prevSatge_ = MapManager::GetInstance()->nowStage_;
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
}


bool MapManager::ChackNowMapTip()
{
    if (MapManager::GetInstance()->prevSatge_ != MapManager::GetInstance()->nowStage_)
    {
        return true;
    }
    return false;
}
