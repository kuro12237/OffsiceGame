#include "SelectScene.h"

void SelectScene::Initialize()
{
	//Mapの読み込み
	MapManager::Initialize();
}

void SelectScene::Update(GameManager* Scene)
{
	MapManager::Update();

	ImguiUpdate(Scene);
	
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

void SelectScene::ImguiUpdate(GameManager* Scene)
{
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.02f, 0.02f, 0.02f, 1.0f));

	ImGui::Begin("SelectScene");
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	if (ImGui::TreeNode("Map"))
	{
		if (ImGui::Button("Map1"))
		{
			MapManager::SetNextMaptip(1);
		}

		if (ImGui::Button("Map2"))
		{
			MapManager::SetNextMaptip(2);
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("SceneChange"))
	{

		if (ImGui::Button("GameScene"))
		{
			Scene->ChangeState(new GameScene);

		}

		ImGui::TreePop();
	}
	ImGui::End();


}
