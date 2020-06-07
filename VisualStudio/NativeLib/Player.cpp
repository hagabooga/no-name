#include "Player.h"




void Player::_register_methods()
{
	register_method("_process", &Player::_physics_process);
	register_method("_unhandled_input", &Player::_unhandled_input);
	register_method("_ready", &Player::_ready);
	register_property<Player, float>("gravity", &Player::gravity, -30.0f);
	register_property<Player, float>("max_speed", &Player::max_speed, 10.0f);
	register_property<Player, float>("max_running_speed", &Player::max_running_speed, 15.0f);
	register_property<Player, float>("accel", &Player::accel, 2.0f);
	register_property<Player, float>("deaccel", &Player::deaccel, 5.0f);
	register_property<Player, float>("jump_height", &Player::jump_height, 15.0f);
	register_property<Player, float>("mouse_sensitivity", &Player::mouse_sensitivity, 0.2f);
	//register_signal<Player>((char *)"position_changed", "node", GODOT_VARIANT_TYPE_OBJECT, "new_pos", GODOT_VARIANT_TYPE_VECTOR2);
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::_init()
{
}

void Player::_ready()
{
	Engine::get_singleton()->set_target_fps(150);
	Engine::get_singleton()->set_iterations_per_second(150);
	input = Input::get_singleton();
	input->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
	camera = cast_to<Camera>(get_node("Camera"));
	line_of_sight = cast_to<RayCast>(camera->get_node("LineOfSight"));
	equipped_gun = cast_to<Gun>(camera->get_node("EquippedGun")->get_node("Gun"));
	ground_raycast = cast_to<RayCast>(get_node("GroundRayCast"));
	pickup_pos = cast_to<Spatial>(get_node("PickupPos"));
	interact_text = cast_to<Control>(get_node("CanvasLayer")->get_node("UnhandledUI")->
		get_node("InteractText"));
	animation_player = cast_to<AnimationPlayer>(get_node("AnimationPlayer"));
	picked_up_obj = NULL;

}

void Player::_physics_process(float delta)
{

	get_input(delta);
	checkInteract();
	if (equipped_gun != NULL)
	{
		if ((equipped_gun->automatic && input->is_action_pressed("fire")) || input->is_action_just_pressed("fire"))
		{
			equipped_gun->fire();
		}
	}
}

void Player::_unhandled_input(InputEvent *ev)
{
	auto *mouse = cast_to<InputEventMouseMotion>(ev);
	if (mouse != NULL)
	{
		rotate_head(mouse);
	}
}

void Player::rotate_head(InputEventMouseMotion *mouse)
{
	Vector2 relative = mouse->get_relative();
	rotate_y(Helper::deg2rad(-relative.x * mouse_sensitivity));
	float change = -relative.y * mouse_sensitivity;
	if (change + camera_angle < 90.0 && change + camera_angle > -90.0f)
	{
		camera->rotate_x(Helper::deg2rad(change));
		camera_angle += change;
	}
}

void Player::get_input(float delta)
{

	Vector3 direction = Vector3();
	Basis aim = camera->get_global_transform().basis;



	if (input->is_action_pressed("ui_right"))
	{
		direction += aim.x;
	}
	if (input->is_action_pressed("ui_left"))
	{
		direction -= aim.x;
	}
	if (input->is_action_pressed("ui_up"))
	{
		direction -= aim.z;
	}
	if (input->is_action_pressed("ui_down"))
	{
		direction += aim.z;
	}
	direction.y = 0;
	direction.normalize();
	bool backflipping = false;
	bool in_air = false;
	if (!ground_raycast->is_colliding() || velocity.y > 0)
	{
		velocity.y += gravity * delta;
		in_air = true;
	}
	else
	{
		if (ground_raycast->is_colliding())
		{
			velocity.y = 0;
		}

		if (input->is_action_just_pressed("ui_select"))
		{
			if (input->is_action_pressed("ctrl"))
			{
				velocity.y = jump_height * 1.6;
				Vector3 dir{};
				dir -= aim.z;
				dir.y = 0;
				dir.normalize();
				velocity -= dir * 5;
				animation_player->play("backflip");
				backflipping = true;
			}
			else
			{
				velocity.y = jump_height;
			}
		}
	}

	if (input->is_action_pressed("ctrl"))
	{
		get_transform().scale(Vector3(1, 1, 0.5));
	}

	Vector3 temp_velocity = velocity;
	temp_velocity.y = 0;



	float acceleration = deaccel;
	if (direction.dot(temp_velocity) > 0)
		acceleration = accel;

	float speed = max_speed;
	if (input->is_action_pressed("shift"))
	{
		speed = max_running_speed;
		acceleration *= 1.15;
	}

	Vector3 target = direction * speed;

	cout << in_air << endl;
	temp_velocity = temp_velocity.linear_interpolate(target,
		(in_air ? acceleration / 5 : acceleration) * delta);
	velocity.x = temp_velocity.x;
	velocity.z = temp_velocity.z;
	velocity = move_and_slide(velocity, Vector3(0, 1, 0));
}

void Player::checkInteract()
{
	bool press_interact_key = input->is_action_just_pressed("grab");
	if (picked_up_obj != NULL)
	{
		if (press_interact_key)
		{
			drop_pickup();
		}
		interact_text->set_visible(false);
	}
	else
	{
		bool see_something = line_of_sight->is_colliding();
		if (see_something)
		{
			Interactable* interactable = cast_to<Interactable>(line_of_sight->get_collider());
			bool is_interactable = interactable != NULL;
			interact_text->set_visible(is_interactable);
			if (press_interact_key && is_interactable)
			{
				interact(interactable);
			}
		}
		else
		{
			interact_text->set_visible(false);
		}
	}

}



void Player::interact(Interactable* interactable)
{

	interactable->interact();
	if (cast_to<Pickable>(line_of_sight->get_collider()) != NULL)
	{
		pickup(cast_to<Pickable>(line_of_sight->get_collider()));
	}
}

void Player::pickup(Pickable* pickable)
{
	if (pickable->get_parent() != NULL)
	{
		pickable->get_parent()->remove_child(pickable);
	}
	pickup_pos->add_child(pickable);
	pickable->set_global_transform(pickup_pos->get_global_transform());
	picked_up_obj = pickable;
}

void Player::drop_pickup()
{
	pickup_pos->remove_child(picked_up_obj);
	get_parent()->add_child(picked_up_obj);
	picked_up_obj->interact();
	picked_up_obj->set_global_transform(pickup_pos->get_global_transform());
	picked_up_obj = NULL;
}

