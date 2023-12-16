#include "SelectScene.h"

void SelectScene::Initialize()
{
	
}

void SelectScene::Update(GameManager* Scene)
{

	if (Input::PushKeyPressed(DIK_P))
	{
		MapManager::SetNextMaptip(2);
	}
	if (Input::PushKeyPressed(DIK_O))
	{
		MapManager::SetNextMaptip(1);

	}

	MapManager::Update();

	if (Input::PushKeyPressed(DIK_L))
	{
		Scene->ChangeState(new GameScene);
	}

}

void SelectScene::Back2dSpriteDraw()
{
}

void SelectScene::Object3dDraw()
{
}

void SelectScene::Flont2dSpriteDraw()
{
}
