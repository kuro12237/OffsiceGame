#include "GameScene.h"

void GameScene::Initialize()
{

	//cameraSetting
	viewProjection_.Initialize();
	viewProjection_.translation_ = { 0.0f,3.0f,-16.0f };
	viewProjection_.UpdateMatrix();

	//天箱
	skyBox_ = make_unique<SkyBox>();
	skyBox_->Initialize();

	//
	sun_ = make_unique<Sun>();
	sun_->Initialize();
	//MapのDraw
	mapObject_ = make_unique<MapObject>();
	mapObject_->Initialize(MapManager::GetMapData());
	//testParticle
	fire_ = make_unique<FireParticle>();
	fire_->Initialize({0.0f,1.0f,-3.0f});
}

void GameScene::Update(GameManager* Scene)
{

	fire_->Update({ 0.0f,1.0f,-3.0f });
	sun_->Update();
	skyBox_->Update();
	mapObject_->Update();

	viewProjection_.UpdateMatrix();

	ImguiUpdate(Scene);

}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
	skyBox_->Draw(viewProjection_);
	mapObject_->Draw(viewProjection_);

	fire_->Draw(viewProjection_);
}

void GameScene::Flont2dSpriteDraw()
{
}

void GameScene::ImguiUpdate(GameManager* Scene)
{


	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.02f, 0.02f, 0.02f, 1.0f));

	ImGui::Begin("GameScene");
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	if (ImGui::TreeNode("Camera"))
	{
		ImGui::DragFloat3("translate", &viewProjection_.translation_.x, -1.0f, 1.0f);
		ImGui::DragFloat3("rotate", &viewProjection_.rotation_.x, -1.0f, 1.0f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Scene"))
	{
		if (ImGui::Button("SelectScene")) {

			Scene->ChangeState(new SelectScene);
		}
		ImGui::TreePop();
	}

	ImGui::End();
}
