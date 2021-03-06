﻿#pragma once

#include <vector>

#include "floor.h"
#include "pattern_line.h"
#include "wall.h"

namespace model
{
	class board
	{
		int m_score{0};
		std::vector<pattern_line> m_pattern_lines;
		wall m_wall;
		floor m_floor;
		bool m_has_starter_tile{false};
	public:
		board();
		// board(const board& other);
		void tile_wall(int pattern_line_index, tile color);
		int get_score() const;

		// iterator methods for display purposes
		std::vector<std::vector<tile>>::const_iterator wall_begin() const;
		std::vector<std::vector<tile>>::const_iterator wall_end() const;
		std::vector<pattern_line>::const_iterator pattern_lines_begin() const;
		std::vector<pattern_line>::const_iterator pattern_lines_end() const;
		std::vector<tile>::const_iterator floor_begin() const;
		std::vector<tile>::const_iterator floor_end() const;
		wall &get_wall() { return m_wall; }
		void add_to_floor(tile color);
		bool has_starter_tile();
		void set_starter_tile(bool cond);
		bool pattern_line_full(int pattern_line_index);
		void add_to_pattern_line(int pattern_line_index, tile tile);
		bool floor_full();
		bool can_add_to_pattern_line(int pattern_line_index, tile tile);
		void take_starter_tile();
		void set_starter_player();
		tile pattern_line_color(int pattern_line_index);
		void clear_pattern_line(int pattern_line_index);
		int score_wall_tile(int pattern_line_index, tile tile);
		std::vector<int> get_score_indices(int pattern_line_index, tile tile);
		int score_floor();
		int floor_to_lid(lid& lid);
		bool handle_floor_starter_tile();
		bool game_finished();
		int score_wall_color(tile tile);
		int score_wall_line(int line);
		int score_wall_row(int row);
		int wall_line_count(int line);
		int get_floor_score();
		int get_pattern_line_score(int pattern_line_index);
		void remove_from_pattern_line(int pattern_line_index, int count);
		void remove_from_floor(int count);
		int horizontal_lines();
		void take_score(int score);
		void lid_to_floor(lid& lid, int count);
		void add_starter_to_floor();
		void wall_to_pattern_line(int pattern_line_index, tile tile);
		int get_pattern_line_tile_count(int pattern_line_index);
	};
}
