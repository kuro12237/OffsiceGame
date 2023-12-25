#pragma once
#include"GameObject/Player/IPlayerCommand.h"

class PlayerMoveTopCommand :public IPlayerCommand
{
public:

	void Exec(Player& player)override;

};