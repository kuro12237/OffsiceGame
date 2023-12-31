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

	worldTransform_.Initialize();

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
		ImGui::DragFloat3("rotate", &viewProjection_.rotation_.x, -1.0f, 1.0f);
		ImGui::TreePop();
	}
	ImGui::End();

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
	//MapManager::SetNextMaptip(SelectStage_);


	worldTransform_.UpdateMatrix();
	
	sun_->Update();
	skyBox_->Update();

	viewProjection_.UpdateMatrix();

}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{

	skyBox_->Draw(viewProjection_);
	MapManager::Draw(viewProjection_);
}

void GameScene::Flont2dSpriteDraw()
{
}
