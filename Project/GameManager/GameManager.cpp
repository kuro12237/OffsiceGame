#include "GameManager.h"

GameManager::GameManager()
{
	Cleyera::Initialize();
	Scene_ = new SelectScene();
	Scene_->Initialize();
	
}

GameManager::~GameManager()
{
	delete Scene_;
	Cleyera::Finalize();
}

void GameManager::Run()
{
	while (WinApp::WinMsg())
	{
		Cleyera::BeginFlame();
	
		LightingManager::ClearList();

		Scene_->Update(this);
		
		LightingManager::TransfarBuffers();
		
		Scene_->Back2dSpriteDraw();
		Scene_->Object3dDraw();
		Scene_->Flont2dSpriteDraw();
	
		Cleyera::EndFlame();
	}
}

void GameManager::ChangeState(IScene *newScene)
{
	delete Scene_;
	Scene_ = newScene;
	Scene_->Initialize();
	return;
}
