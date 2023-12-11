#pragma once
#include"IModelState.h"
#include"Model.h"
#include"ModelManager.h"
#include"VectorTransform.h"
#include"Light/LightingManager.h"

class ModelObjState :public IModelState
{
public:
	ModelObjState() {};
	~ModelObjState() ;

	void Initialize(Model* state)override;

	void Draw(Model* state, const WorldTransform& worldTransform, const ViewProjection& viewprojection)override;

private:

    ID3D12Resource* CreateBufferResource(size_t sizeInbyte);

	ResourcePeroperty resource_ = {};
	Vector3 testLightDirection = { 0,-1.0f,0 };
};