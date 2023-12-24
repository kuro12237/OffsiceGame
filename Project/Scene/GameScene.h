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

#include"GameObject/Player/Player.h"
#include"GameObject/Player/PlayerInputHandler.h"

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
	int SelectStage_ = 1;

	void PlayerInput();
	
	unique_ptr<SkyBox>skyBox_ = nullptr;
	unique_ptr<Sun>sun_ = nullptr;

	unique_ptr<Player>player_ = nullptr;
	unique_ptr<PlayerIputHandler>playerInputHandler_ = nullptr;
	IPlayerCommand* playerCommand_ = nullptr;
};