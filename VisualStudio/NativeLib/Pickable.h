#pragma once
#include "Common.h"
#include <MeshInstance.hpp>
#include "Interactable.h"

class Pickable : public Interactable
{
	GODOT_SUBCLASS(Pickable, Interactable);
private:
	//bool picked_up = false;
	//Spatial *holder;
public:
	static void _register_methods();

	Pickable();
	~Pickable();

	void _init() override;
	void _ready() override;

	void _process(float delta);

	void picked();
	void dropped();
	// player should throw item
	//void carry();
	//void drop();
	//void throw_item(float power);

};