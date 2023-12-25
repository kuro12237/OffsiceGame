#include "PlayerMoveDownCommand.h"

void PlayerMoveDownCommand::Exec(Player& player)
{
	player.DownMove();
}
