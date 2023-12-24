#pragma once
#include"GameObject/Player/IPlayerCommand.h"

class PlayerMoveRightCommand :public IPlayerCommand
{
public:

	void Exec(Player& player)override;

};
