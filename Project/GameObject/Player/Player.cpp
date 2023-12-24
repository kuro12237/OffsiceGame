#include "Player.h"

void Player::Initialize(Vector3 pos)
{
	this->modelHandle_ = ModelManager::LoadObjectFile("Player");

	this->model_ = make_unique<Game3dObject>();
	this->model_->Create();
	this->model_->SetModel(this->modelHandle_);

	this->worldTransform_.Initialize();
	this->worldTransform_.translate = pos;
	this->worldTransform_.scale = { 0.5f,0.5f,0.5f };
}

void Player::Update()
{
	if (ImGui::TreeNode("Player"))
	{
		ImGui::DragFloat3("translate", &this->worldTransform_.translate.x, -0.5f, 0.5f);
		ImGui::TreePop();
	}


	this->worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection view)
{
	this->model_->Draw(this->worldTransform_, view);

}

void Player::LeftMove()
{
	worldTransform_.translate.x = worldTransform_.translate.x - 0.1f;
}

void Player::RightMove()
{
	worldTransform_.translate.x = worldTransform_.translate.x + 0.1f;
}
