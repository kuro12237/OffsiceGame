#pragma once
#include"Game3dObject.h"

class Player
{
public:
	Player() {};
	~Player() {};

	void Initialize(Vector3 pos);

	void Update();

	void Draw(ViewProjection view);

	void LeftMove();

	void RightMove();

private:

	WorldTransform worldTransform_;
	unique_ptr<Game3dObject>model_ = nullptr;
	uint32_t modelHandle_ = 0;


};