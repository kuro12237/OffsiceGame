#pragma once
#include"IPlayerCommand.h"
#include"Input.h"
#include"Commands/PlayerMoveLeftCommand.h"
#include"Commands/PlayerMoveRightCommand.h"

class PlayerIputHandler
{
public:
	
	IPlayerCommand* HandleInput();

	void AssignMoveLeftA();

	void AssignMoveRightD();

private:

	unique_ptr<IPlayerCommand> pressKeyD_ = nullptr;
	unique_ptr<IPlayerCommand> pressKeyA_ = nullptr;


};