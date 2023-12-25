#pragma once
#include"Pch.h"

enum MapDirection
{
	TOP,
	DOWN,
	RIGHT,
	LEFT
};

class MapCollider
{
public:
	virtual ~MapCollider() {};

	virtual void OnMapCollision(MapDirection direction) = 0;

	virtual Vector3 GetWorldPosition() = 0;

	void SetSize(Vector2 size) { size_ = size; }
	void SetVelocity_(Vector2 v) { velocity_ = v; }


	Vector2 GetSize_() { return size_; }
	Vector2 GetVelocity() { return velocity_; }
	

private:
	Vector2 size_ = { 0.5f,0.5f };
	Vector2 velocity_ = {};
};
