#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"Input.h"
#include"AudioManager.h"
#include"FileLoader.h"
#include"CollisionManager.h"
#include"Particle/Particle.h"
#include"ModelManager.h"
#include"Light/Light.h"
#include"DebugTools/DebugTools.h"
#include"GameObject/SkyBox/SkyBox.h"


class GameScene :public IScene
{
public:
	GameScene() {};
	~GameScene() {};


	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

private:

	ViewProjection viewProjection_{};

	unique_ptr<Model>model_ = nullptr;
	WorldTransform worldTransform_{};

	unique_ptr<SkyBox>skyBox_ = nullptr;
};