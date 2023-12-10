#include "Sun.h"

void Sun::Initialize()
{
	Light_.position = { 204.0f,134.0f,-226.0f };
	Light_.radious = 589.0f;
	Light_.decay = 0.5f;

}

void Sun::Update()
{
	ImGui::Begin("Light");

	ImGui::ColorPicker3("colorB", &Light_.color.x);
	ImGui::DragFloat3("posB", &Light_.position.x, -1.0f, 1.0f);
	ImGui::DragFloat("intensityB", &Light_.intencity, -1.0f, 1.0f);
	ImGui::DragFloat("radiousB", &Light_.radious, -1.0f, 1.0f);
	ImGui::DragFloat("decayB", &Light_.decay, -1.0f, 1.0f);

	ImGui::End();

	LightingManager::AddList(Light_);
}
