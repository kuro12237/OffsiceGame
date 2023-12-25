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
	//if (ImGui::TreeNode("Player"))
	{
		//ImGui::DragFloat3("translate", &this->worldTransform_.translate.x, -0.5f, 0.5f);
		//ImGui::TreePop();
	}
	
	SetVelocity_(this->velocity_);

}

void Player::Move()
{
	this->worldTransform_.translate.x += this->velocity_.x;
	this->worldTransform_.translate.y += this->velocity_.y;
	
	velocity_ = {};

	this->worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection view)
{
	this->model_->Draw(this->worldTransform_, view);

}

void Player::LeftMove()
{
	this->velocity_.x = - 0.1f;
}

void Player::RightMove()
{

    this->velocity_.x = 0.1f;
	
}

void Player::TopMove()
{
	this->velocity_.y = 0.1f;
}

void Player::DownMove()
{
	this->velocity_.y = -0.1f;
}

void Player::OnMapCollision(MapDirection direction)
{
	if (direction == RIGHT || direction == LEFT)
	{
		velocity_.x = 0;
	}
	if (direction == TOP || direction == DOWN)
	{
		velocity_.y = 0;
	}
}

Vector3 Player::GetWorldPosition()
{
	Vector3 pos{};
	pos.x = worldTransform_.matWorld.m[3][0];
	pos.y = worldTransform_.matWorld.m[3][1];
	pos.z = worldTransform_.matWorld.m[3][2];

	return pos;
}
