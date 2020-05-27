#include "Pickable.h"

void Pickable::_register_methods()
{
	register_method("_process", &Pickable::_process);
	register_method("_ready", &Pickable::_ready);
}

Pickable::Pickable() : Interactable::Interactable()
{
}

Pickable::~Pickable()
{

}

void Pickable::_init()
{

}

void Pickable::_ready()
{
	Interactable::_ready();
}

void Pickable::_process(float delta)
{
	//if (picked_up)
	//{
	//	set_global_transform(holder->get_global_transform());
	//}
}

void Pickable::picked()
{
	collision_shape->set_disabled(true);
	//get_transform().origin = Vector3(0, 0, 0);
	set_mode(MODE_STATIC);
}

void Pickable::dropped()
{
	collision_shape->set_disabled(false);
	set_mode(MODE_RIGID);
}

//void Pickable::pick_up(Spatial *pickup_pos_node)
//{
//	Godot::print("Pick up");
//	//holder = pickup_pos_node;
//	//if (picked_up)
//	//{
//	//	drop();
//	//}
//	//else
//	//{
//	//	Godot::print("else");
//	//	carry();
//	//}
//}

//void Pickable::carry()
//{
//	//Godot::print("carry");
//	//auto *collision_shape = cast_to<CollisionShape>(get_node("CollisionShape"));
//	//collision_shape->set_disabled(true);
//	//set_mode(1);
//	//picked_up = true;
//}
//
//void Pickable::drop()
//{
//	//auto *collision_shape = cast_to<CollisionShape>(get_node("CollisionShape"));
//	//collision_shape->set_disabled(false);
//	//set_mode(0);
//	//picked_up = false;
//}
//
//void Pickable::throw_item(float power)
//{
//	//pass
//}