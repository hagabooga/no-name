#pragma once
#include "Common.h"
#include "Interactable.h"

class Pickable : public Interactable
{
	GODOT_SUBCLASS(Pickable, Interactable);
private:
	bool picked_up = false;
public:
	static void _register_methods();

	Pickable();
	~Pickable();

	void _init() override;
	void _ready() override;

	void _process(float delta);

	void interact() override;

	// player should throw item
	//void carry();
	//void drop();
	//void throw_item(float power);

};