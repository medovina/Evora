﻿#include "Tile.h"
#include <Node2D.hpp>
#include <Label.hpp>
#include <string>

using namespace godot;

void Tile::_register_methods()
{
	register_method("_process", &Tile::_process);
	register_method("_on_mouse_entered", &Tile::_on_mouse_entered);
	register_method("_area_input_event", &Tile::_area_input_event);
}

void Tile::_init()
{
	_label = (Label*)get_child(1);
	_input = Input::get_singleton();
}

void Tile::_process(float delta)
{
	if(_holding)
	{
		set_global_position(get_global_mouse_position());
	}
}

void Tile::_on_mouse_entered()
{
	++_enter_count;
	Label* label = (Label*)get_child(1);
	label->set_text(String(std::to_string(_enter_count).c_str()));
}

void Tile::_area_input_event()
{
	int64_t mouse_button_mask = _input->get_mouse_button_mask();
	if(mouse_button_mask & 1) // left mouse button pressed
	{
		_holding = true;
	}
	else
	{
		_holding = false;
	}
	
}

Tile::Tile()
{
}