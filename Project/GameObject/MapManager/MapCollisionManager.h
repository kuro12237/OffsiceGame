#pragma once
#include"MapCollider.h"
#include"MapManager.h"

struct SCubeMapVertex
{
	float top, down, right, left;
};


class MapCollisionManager
{
public:
	MapCollisionManager() {};
	~MapCollisionManager() {};

	void liseClear() { colliders_.clear(); }

	void PushCollider(MapCollider* c) { colliders_.push_back(c); }

	void CheckCollion();

private:

	bool CheckLeftRight(vector<vector<uint32_t>>map, SCubeMapVertex c, Vector2 velo);

	bool CheckBlockRight(vector<vector<uint32_t>>map, SCubeMapVertex c);
	bool CheckBlockLeft(vector<vector<uint32_t>>map, SCubeMapVertex c);

	bool CheckTopDown(vector<vector<uint32_t>>map, SCubeMapVertex c, Vector2 velo);

	bool CheckBlockTop(vector<vector<uint32_t>>map, SCubeMapVertex c);
	bool CheckBlockDown(vector<vector<uint32_t>>map, SCubeMapVertex c);


	/// <summary>
	/// checkする周りに壁があればチェックする
	/// </summary>
	void CheckMapTip(MapCollider* c);

	list<MapCollider*>colliders_;

};
