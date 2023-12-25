#pragma once
#include"IPlayerCommand.h"
#include"Input.h"
#include"Commands/PlayerMoveLeftCommand.h"
#include"Commands/PlayerMoveRightCommand.h"
#include"Commands/PlayerMoveTopCommand.h"
#include"Commands/PlayerMoveDownCommand.h"

class PlayerIputHandler
{
public:
	
	IPlayerCommand* HandleInput();

	void AssignMoveLeftA();

	void AssignMoveRightD();

	void AssignMoveTopW();

	void AssignMoveDownS();


private:

	unique_ptr<IPlayerCommand> pressKeyD_ = nullptr;
	unique_ptr<IPlayerCommand> pressKeyA_ = nullptr;
	unique_ptr<IPlayerCommand> pressKeyW_ = nullptr;
	unique_ptr<IPlayerCommand> pressKeyS_ = nullptr;

};