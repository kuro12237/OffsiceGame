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
#include"GameObject/MapManager/MapManager.h"
#include"Light/LightingManager.h"
#include"GameObject/Sun/Sun.h"
#include"GameObject/MapManager/MapObject.h"

#include"Scene/SelectScene.h"

#include"GameObject/FireParticles/FireParticle.h"

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

	void ImguiUpdate(GameManager* Scene);

	ViewProjection viewProjection_{};

	unique_ptr<SkyBox>skyBox_ = nullptr;
	unique_ptr<Sun>sun_ = nullptr;
	int SelectStage_ = 1;
	unique_ptr<MapObject>mapObject_ = nullptr;

	unique_ptr<FireParticle>fire_ = nullptr;
};