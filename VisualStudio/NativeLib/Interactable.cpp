#include "Interactable.h"

void Interactable::_register_methods()
{
	//register_method("_process", &Interactable::_process);
	//register_method("_ready", &Interactable::_ready);
}

Interactable::Interactable()
{
}

Interactable::~Interactable()
{
}

void Interactable::_init()
{
}

void Interactable::_ready()
{
	collision_shape = cast_to<CollisionShape>(get_node("CollisionShape"));
}
