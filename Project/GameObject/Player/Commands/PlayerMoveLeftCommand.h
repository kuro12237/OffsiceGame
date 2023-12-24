#pragma once
#include"GameObject/Player/IPlayerCommand.h"

class PlayerMoveLeftCommand:public IPlayerCommand
{
public:
	
	void Exec(Player& player)override;

};
