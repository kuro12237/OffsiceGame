#pragma once
#include"GameObject/Player/IPlayerCommand.h"

class PlayerMoveDownCommand :public IPlayerCommand
{
public:

	void Exec(Player& player)override;

};