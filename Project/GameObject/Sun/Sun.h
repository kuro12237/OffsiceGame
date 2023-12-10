#pragma once
#include"Light/Light.h"
#include"Light/LightingManager.h"

class Sun
{
public:
	Sun() {};
	~Sun() {};

	void Initialize();

	void Update();

private:

	PointLight_param Light_;

};