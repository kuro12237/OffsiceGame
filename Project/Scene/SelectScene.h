#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"Input.h"
#include"GameScene.h"
#include"GameObject/MapManager/MapManager.h"

class SelectScene :public IScene
{
public:
	SelectScene() {};
	~SelectScene() {};


	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

private:


};