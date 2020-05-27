#pragma once

#include "Common.h"
#include "Interactable.h"
#include <AnimationPlayer.hpp>

class Door : public Interactable
{
	GODOT_SUBCLASS(Door, Interactable);

private:
	bool is_open = false;
	AnimationPlayer* animation_player;

public:
	static void _register_methods();

	Door();
	~Door();

	void _init() override;
	void _ready() override;
	void _process(float delta);

	void interact() override;

};