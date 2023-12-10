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

	sun_ = make_unique<Sun>();
	sun_->Initialize();

	model_ = make_unique<Model>();
	model_->SetModel(modelHandle);

	worldTransform_.Initialize();

	MapManager::Initialize();
}

void GameScene::Update(GameManager* Scene)
{
	MapManager::Update();
	Scene;

	ImGui::Begin("MapSelect");
	ImGui::InputInt("StageNumber", &SelectStage_);
	ImGui::End();
	
	MapManager::SetNextMaptip(SelectStage_);

	if (Input::PushKey(DIK_W))
	{
		viewProjection_.translation_.y += 0.1f;
	}
	if (Input::PushKey(DIK_S))
	{
		viewProjection_.translation_.y -= 0.1f;
	}

	if (Input::PushKey(DIK_A))
	{
		viewProjection_.translation_.x -= 0.1f;
	}	if (Input::PushKey(DIK_D))
	{
		viewProjection_.translation_.x += 0.1f;
	}

	if (Input::PushKey(DIK_LEFT))
	{
		viewProjection_.rotation_.y -= 0.03f;
	}	if (Input::PushKey(DIK_RIGHT))
	{
		viewProjection_.rotation_.y += 0.03f;
	}

	worldTransform_.UpdateMatrix();
	
	sun_->Update();
	skyBox_->Update();

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
	//model_->Draw(worldTransform_, viewProjection_);
	MapManager::Draw(viewProjection_);
}

void GameScene::Flont2dSpriteDraw()
{
}
