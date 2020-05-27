#include "Door.h"

void Door::_register_methods()
{
	register_method("_process", &Door::_process);
	register_method("_ready", &Door::_ready);
}

Door::Door() : Interactable::Interactable()
{
}

Door::~Door()
{
}

void Door::_init()
{
}

void Door::_ready()
{
	Interactable::_ready();
	animation_player = cast_to<AnimationPlayer>(find_node("AnimationPlayer"));
}

void Door::_process(float delta)
{
}

void Door::interact()
{
	if (!animation_player->is_playing())
	{
		is_open = !is_open;
		if (is_open)
		{
			animation_player->play("open");
		}
		else
		{
			animation_player->play("close");
		}
	}

}
