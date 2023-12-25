#include "PlayerInputHandler.h"

IPlayerCommand* PlayerIputHandler::HandleInput()
{
	if (Input::PushKey(DIK_A))
	{
		return pressKeyA_.get();
	}
	else if(Input::PushKey(DIK_D))
	{
		return pressKeyD_.get();
	}

	if (Input::PushKey(DIK_W))
	{
		return pressKeyW_.get();
	}
	else if (Input::PushKey(DIK_S))
	{
		return pressKeyS_.get();
	}

	return nullptr;
}

void PlayerIputHandler::AssignMoveLeftA()
{
	unique_ptr<IPlayerCommand> command = make_unique<PlayerMoveLeftCommand>();
	this->pressKeyA_ = move(command);
}

void PlayerIputHandler::AssignMoveRightD()
{
	unique_ptr<IPlayerCommand> command = make_unique<PlayerMoveRightCommand>();
	this->pressKeyD_ = move(command);
}

void PlayerIputHandler::AssignMoveTopW()
{
	unique_ptr<IPlayerCommand> command = make_unique<PlayerMoveTopCommand>();
	this->pressKeyW_ = move(command);
}

void PlayerIputHandler::AssignMoveDownS()
{
	unique_ptr<IPlayerCommand> command = make_unique<PlayerMoveDownCommand>();
	this->pressKeyS_ = move(command);
}
