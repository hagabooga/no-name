#pragma once
#include "Common.h"
#include <Spatial.hpp>
#include <AnimationPlayer.hpp>
#include <Timer.hpp>
#include <AudioStreamSample.hpp>
#include <AudioStreamPlayer.hpp>
#include <ResourceLoader.hpp>

class Gun : public Spatial
{
	GODOT_CLASS(Gun, Spatial);

private:
	AnimationPlayer* anim;
	float ROF = 1.0f;
	Ref<AudioStreamSample> gunshot_sound;


public:
	bool automatic = false;

	static void _register_methods();

	Gun();
	~Gun();
	void _init();
	void _ready();
	void fire();




	void play_gunshot_sound();

};


