#include "score_wall_tile.h"

using namespace control;

void control::score_wall_tile::execute(std::shared_ptr<model::game> game)
{
	m_score = game->score_wall_tile(m_player_index, m_line, m_color);
}

void score_wall_tile::unexecute(std::shared_ptr<model::game> game)
{
	game->take_score(m_player_index, m_score);
}

std::unique_ptr<command> score_wall_tile::clone()
{
	return std::make_unique<score_wall_tile>(*this);
}

bool score_wall_tile::is_move()
{
	return false;
}

int score_wall_tile::player_index()
{
	return -1;
}
