#pragma once
#include"Game3dObject.h"
#include"GameObject/MapManager/MapCollider.h"

class Player:public MapCollider
{
public:
	Player() {};
	~Player() {};

	void Initialize(Vector3 pos);

	void Update();

	void Move();

	void Draw(ViewProjection view);

	void LeftMove();

	void RightMove();

	void TopMove();

	void DownMove();

	void OnMapCollision(MapDirection direction)override;

	Vector3 GetWorldPosition()override;

private:

	WorldTransform worldTransform_;
	unique_ptr<Game3dObject>model_ = nullptr;
	uint32_t modelHandle_ = 0;

	Vector2 velocity_ = {};
};