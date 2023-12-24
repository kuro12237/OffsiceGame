#include "PlayerMoveRightCommand.h"

void PlayerMoveRightCommand::Exec(Player& player)
{
	player.RightMove();
}
