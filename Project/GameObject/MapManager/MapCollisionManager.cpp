#include "MapCollisionManager.h"

void MapCollisionManager::CheckCollion()
{

	std::list<MapCollider*>::iterator itrA = colliders_.begin();

	for (; itrA != colliders_.end(); ++itrA) {

		MapCollider* collider = *itrA;

		CheckMapTip(collider);

	}

}

bool MapCollisionManager::CheckLeftRight(vector<vector<uint32_t>>map, SCubeMapVertex c, Vector2 velo)
{
	if (map[(int)(MAP_MAX_Y - c.top)][(int)(c.left + velo.x)] != 0 || map[(int)(MAP_MAX_Y - c.top)][(int)(c.right + velo.x)] != 0 ||
		map[(int)(MAP_MAX_Y - c.down)][(int)(c.left + velo.x)] != 0 || map[(int)(MAP_MAX_Y - c.down)][(int)(c.right + velo.x)] != 0
		)
	{
		return true;
	}
	return false;
}

bool MapCollisionManager::CheckBlockLeft(vector<vector<uint32_t>> map, SCubeMapVertex c)
{
	while (map[(int)(MAP_MAX_Y - c.top)][(int)(c.left) - 1] == 0 && map[(int)(MAP_MAX_Y - c.top)][(int)(c.right) - 1] == 0 &&
		map[(int)(MAP_MAX_Y - c.down)][(int)(c.left) - 1] == 0 && map[(int)(MAP_MAX_Y - c.down)][(int)(c.right) - 1] == 0
		)
	{
		return true;
	}
	return false;
}

bool MapCollisionManager::CheckTopDown(vector<vector<uint32_t>> map, SCubeMapVertex c, Vector2 velo)
{
	if (map[(int)(MAP_MAX_Y - ( c.top + velo.y))][(int)(c.left)] != 0 || map[(int)(MAP_MAX_Y - (c.top + velo.y))][(int)(c.right)] != 0 ||
		map[(int)(MAP_MAX_Y - (c.down + velo.y))][(int)(c.left)] != 0 || map[(int)(MAP_MAX_Y - (c.down + velo.y))][(int)(c.right)] != 0
		)
	{
		return true;
	}
	return false;
}

bool MapCollisionManager::CheckBlockTop(vector<vector<uint32_t>> map, SCubeMapVertex c)
{
	while (map[(int)(MAP_MAX_Y - (c.top + 1))][(int)(c.left)] == 0 && map[(int)((MAP_MAX_Y - c.top + 1))][(int)(c.right)] == 0 &&
		map[(int)(MAP_MAX_Y - (c.down + 1))][(int)(c.left)] == 0 && map[(int)(MAP_MAX_Y - (c.down + 1))][(int)(c.right)] == 0
		)
	{
		return true;
	}
	return false; 
}

bool MapCollisionManager::CheckBlockDown(vector<vector<uint32_t>> map, SCubeMapVertex c)
{
	while (map[(int)(MAP_MAX_Y - (c.top - 1))][(int)(c.left)] == 0 && map[(int)(MAP_MAX_Y - (c.top - 1))][(int)(c.right)] == 0 &&
		map[(int)(MAP_MAX_Y - (c.down - 1))][(int)(c.left)] == 0 && map[(int)(MAP_MAX_Y - (c.down - 1))][(int)(c.right)] == 0
		)
	{
		return true;
	}
	return false;
}

bool MapCollisionManager::CheckBlockRight(vector<vector<uint32_t>> map, SCubeMapVertex c)
{

	while (map[(int)(MAP_MAX_Y - c.top)][(int)(c.left) + 1] == 0 && map[(int)(MAP_MAX_Y - c.top)][(int)(c.right) + 1] == 0 &&
		map[(int)(MAP_MAX_Y - c.down)][(int)(c.left) + 1] == 0 && map[(int)(MAP_MAX_Y - c.down)][(int)(c.right) + 1] == 0
		)
	{
		return true;
	}

	return false;
}


void MapCollisionManager::CheckMapTip(MapCollider * c)
{
	vector<vector<vector<uint32_t>>> map = MapManager::GetMapTipData();
	//とりあえず仮で手前のマップだけに
	vector<vector<uint32_t>> map2d = map[0];

	//中心
	Vector2 pos{};
	pos.x = c->GetWorldPosition().x;
	pos.y = c->GetWorldPosition().y;

	//十字
	SCubeMapVertex vertex{};
	vertex.top = c->GetWorldPosition().y-0.1f ;
	vertex.down = c->GetWorldPosition().y - c->GetSize_().y * 2+0.1f;
	vertex.right = c->GetWorldPosition().x + (c->GetSize_().x * 2 - 0.2f);
	vertex.left = c->GetWorldPosition().x+0.1f;// -c->GetSize_().x;


	Vector2 velocity = c->GetVelocity();

	//左右移動チェック
	if (CheckLeftRight(map2d,vertex,velocity))
	{
		//左に移動しているとき
		if (velocity.x > 0.0f)
		{
			//ブロックの右側をチェック
			if (!CheckBlockRight(map2d, vertex))
			{
				c->OnMapCollision(RIGHT);
			}
		}
		//右に移動しているとき
		if (velocity.x < 0.0f)
		{
			if (!CheckBlockLeft(map2d,vertex))
			{
				c->OnMapCollision(LEFT);
			}
		}
	}

	//左右移動チェック
	if (CheckTopDown(map2d, vertex, velocity))
	{
		//左に移動しているとき
		if (velocity.y > 0.0f)
		{
			//ブロックの右側をチェック
			if (!CheckBlockTop(map2d, vertex))
			{
				c->OnMapCollision(TOP);
			}
		}
		//右に移動しているとき
		if (velocity.y < 0.0f)
		{
			if (!CheckBlockDown(map2d, vertex))
			{
				c->OnMapCollision(DOWN);
			}
		}
	}
}
