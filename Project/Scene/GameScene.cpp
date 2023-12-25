#include "GameScene.h"

void GameScene::Initialize()
{

	//cameraSetting
	viewProjection_.Initialize();
	viewProjection_.translation_ = { 0.0f,3.0f,-16.0f };
	viewProjection_.UpdateMatrix();

	
	skyBox_ = make_unique<SkyBox>();
	skyBox_->Initialize();

	sun_ = make_unique<Sun>();
	sun_->Initialize();

	player_ = make_unique<Player>();
	player_->Initialize({5,5,0});


	playerInputHandler_ = make_unique<PlayerIputHandler>();
	playerInputHandler_->AssignMoveLeftA();
	playerInputHandler_->AssignMoveRightD();
	playerInputHandler_->AssignMoveDownS();
	playerInputHandler_->AssignMoveTopW();
	player_->Update();
	player_->Move();

	mapCollisionManager_ = make_unique<MapCollisionManager>();

	MapManager::Initialize();
}

void GameScene::Update(GameManager* Scene)
{
	MapManager::Update();
	Scene;
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.02f, 0.02f, 0.02f, 1.0f));

	ImGui::Begin("GameScene");
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	if (ImGui::TreeNode("Map"))
	{
		ImGui::InputInt("StageNumber", &SelectStage_);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Camera"))
	{
		ImGui::DragFloat3("translate", &viewProjection_.translation_.x, -1.0f, 1.0f);
		ImGui::DragFloat3("rotate", &viewProjection_.rotation_.x, -0.1f, 0.1f);
		ImGui::TreePop();
	}
	

	if (Input::PushKeyPressed(DIK_P))
	{
		MapManager::SetNextMaptip(2);
	}
	if (Input::PushKeyPressed(DIK_O))
	{
		MapManager::SetNextMaptip(1);

	}
	if (Input::PushKeyPressed(DIK_J))
	{
		skyBox_ = make_unique<SkyBox>();
		skyBox_->Initialize();
	}

	PlayerInput();
	player_->Update();

	mapCollisionManager_->liseClear();
	mapCollisionManager_->PushCollider(player_.get());
	mapCollisionManager_->CheckCollion();
	
	player_->Move();

	sun_->Update();
	skyBox_->Update();

	ImGui::End();

	viewProjection_.UpdateMatrix();

}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
	player_->Draw(viewProjection_);
	skyBox_->Draw(viewProjection_);

	MapManager::Draw(viewProjection_);
}

void GameScene::Flont2dSpriteDraw()
{
}

void GameScene::PlayerInput()
{
	playerCommand_ = playerInputHandler_->HandleInput();
	if (this->playerCommand_)
	{
		playerCommand_->Exec(*player_);
	}
}
