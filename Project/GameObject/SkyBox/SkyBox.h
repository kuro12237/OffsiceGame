#pragma once
#include"Game3dObject.h"

class SkyBox
{
public:
	SkyBox() {};
	~SkyBox() 
	{
		model_;
	};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);


private:

	WorldTransform worldTransform_ = {};
	unique_ptr<Game3dObject>model_ = nullptr;

};
