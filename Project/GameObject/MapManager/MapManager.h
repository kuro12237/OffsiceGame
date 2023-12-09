#pragma once
#include"ModelManager.h"
#include"ViewProjection.h"

class MapManager
{
public:
	MapManager() {};
	~MapManager() {};

	static MapManager* GetInstance();

	static void Initialize();

	static void Draw(ViewProjection view);


private:

	static void FileLoad();

	


};