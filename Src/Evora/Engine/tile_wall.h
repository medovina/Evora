﻿#pragma once
#include "command.h"

namespace control
{
	class tile_wall :public command
	{
	public:
		tile_wall(int player_index, int pattern_line_index)
			: m_player_index(player_index),
			  m_pattern_line_index(pattern_line_index)
		{}

		void execute(std::shared_ptr<model::game> game) override;
		void unexecute(std::shared_ptr<model::game> game) override;
		std::unique_ptr<command> clone() override;
		bool is_move() override;
		int player_index() override;
	private:
		int m_player_index;
		int m_pattern_line_index; // here moved to lid would be always equal to pattern line index
		model::tile m_color = model::tile::empty;
	};
}
