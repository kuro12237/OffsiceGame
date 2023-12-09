#pragma once
#include"Model.h"

class SkyBox
{
public:
	SkyBox() {};
	~SkyBox() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);


private:

	WorldTransform worldTransform_ = {};
	unique_ptr<Model>model_ = nullptr;


};
