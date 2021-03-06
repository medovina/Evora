﻿#pragma once
#include <core/Godot.hpp>
#include <Control.hpp>
#include <vector>
#include <Node2D.hpp>

namespace godot
{
	class Floor :public Node2D
	{
		GODOT_CLASS(Floor, Node2D)
	public:
		int m_tile_count;
		static void _register_methods();
		void _init();
		bool is_mouse_over();
		void set_highlight(bool cond);
		void tile_moved(Vector2 position, int color);
		std::vector<Vector2> get_n_positions(int n);
	};
}
