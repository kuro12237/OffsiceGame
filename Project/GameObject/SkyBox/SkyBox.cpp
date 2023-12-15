#include "SkyBox.h"

void SkyBox::Initialize()
{
	uint32_t modelHandle = ModelManager::LoadObjectFile("SkyBox");

	model_ = make_unique<Game3dObject>();

	model_->Create();
	model_->UseLight(true);
	model_->SetModel(modelHandle);

	worldTransform_.Initialize();
}

void SkyBox::Update()
{
	worldTransform_.UpdateMatrix();
}

void SkyBox::Draw(ViewProjection view)
{
	model_->Draw(worldTransform_, view);
}
