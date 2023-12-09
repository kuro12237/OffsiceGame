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
}

void GameScene::Update(GameManager* Scene)
{
	Scene;

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
}

void GameScene::Flont2dSpriteDraw()
{
}
