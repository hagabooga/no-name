#pragma once
#include "Common.h"
#include "Pickable.h"
#include <KinematicBody.hpp>
#include <Input.hpp>
#include <InputEventMouseMotion.hpp>
#include <InputEventMouseButton.hpp>
#include <Engine.hpp>
#include <Camera.hpp>
#include <RayCast.hpp>
#include <PhysicsBody.hpp>
#include <AnimationPlayer.hpp>
#include <RigidBody.hpp>

class Player : public KinematicBody
{
	GODOT_CLASS(Player, KinematicBody);

private:
	// inspector variables
	float gravity = -30.0f;
	float max_speed = 10.0f;
	float max_running_speed = 15.0f;
	float accel = 2.0f;
	float deaccel = 5.0f;
	float jump_height = 15.0f;
	float mouse_sensitivity = 0.2f;

	float camera_angle = 0.0f;
	Vector3 velocity = Vector3();
	Camera* camera;
	Input* input;
	RayCast* line_of_sight;
	Pickable* held_body;



public:
	static void _register_methods();

	Player();
	~Player();

	void _init(); // our initializer called by Godot
	void _ready();
	void _physics_process(float delta);
	void _unhandled_input(InputEvent* ev);


	void rotate_head(InputEventMouseMotion* mouse);
	void get_input(float delta);

	void look();
	void pickup();
	void set_pickable(Pickable* pickable);


};

