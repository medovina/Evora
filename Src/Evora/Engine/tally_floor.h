﻿#pragma once
#include "command.h"

namespace control
{
	class tally_floor :public command
	{
	public:
		tally_floor(std::shared_ptr<model::game> game, int player_index)
			: command(game),
			  m_player_index(player_index)
		{}

		void Execute() override;
		void Unexecute() override;
	private:
		int m_player_index;
		int m_score = 0;
		int m_starter_tile_position = 0;
		// the floor size here won't include the starter tile
		int m_floor_size = 0;
	};
}
