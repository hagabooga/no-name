#include "Gun.h"

void Gun::_register_methods()
{
	register_method("_ready", &Gun::_ready);
	register_property<Gun, float>("ROF", &Gun::ROF, 1.0f);
	register_property<Gun, bool>("automatic", &Gun::automatic, false);
	register_property<Gun, Ref<AudioStreamSample>>("gunshot_sound",
		&Gun::gunshot_sound, NULL);
	register_method("fire", &Gun::fire);
	register_method("play_gunshot_sound", &Gun::play_gunshot_sound);
	//cast_to<AudioStreamSample>(ResourceLoader::get_singleton()->load("sounds/gunshot.wav")->_new()));
}

Gun::Gun()
{
}

Gun::~Gun()
{
}

void Gun::_init()
{
}


void Gun::_ready()
{
	anim = cast_to<AnimationPlayer>(get_node("AnimationPlayer"));
	anim->set_speed_scale(ROF);
}

void Gun::fire()
{
	anim->play("fire");

}

void Gun::play_gunshot_sound()
{
	auto* player = AudioStreamPlayer::_new();
	player->connect("finished", player, "queue_free");
	add_child(player);
	player->set_stream(gunshot_sound);
	player->play();
}
