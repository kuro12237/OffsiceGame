#include "GameScene.h"

void GameScene::Initialize()
{
	Grid* grid = new Grid();
	grid->Initialize();
	DebugTools::addCommand(grid, "grid");

	//cameraSetting
	viewProjection_.Initialize();
	viewProjection_.translation_ = { 0.0f,3.0f,-16.0f };
	viewProjection_.UpdateMatrix();

	uint32_t modelHandle = ModelManager::LoadObjectFile("TestWoodBlock");

	skyBox_ = make_unique<SkyBox>();
	skyBox_->Initialize();

	model_ = make_unique<Model>();
	model_->SetModel(modelHandle);

	worldTransform_.Initialize();
}

void GameScene::Update(GameManager* Scene)
{
	Scene;

	skyBox_->Update();

	worldTransform_.UpdateMatrix();

	DebugTools::UpdateExecute(0);
	viewProjection_.UpdateMatrix();
	viewProjection_ = DebugTools::ConvertViewProjection(viewProjection_);
}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
	DebugTools::DrawExecute(0);

	skyBox_->Draw(viewProjection_);
	model_->Draw(worldTransform_, viewProjection_);
}

void GameScene::Flont2dSpriteDraw()
{
}
