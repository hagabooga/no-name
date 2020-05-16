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
	// add your cleanup here
}

void Player::_init()
{
}

void Player::_ready()
{
	Engine::get_singleton()->set_target_fps(150);
	input = Input::get_singleton();
	input->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
	camera = cast_to<Camera>(get_node("Camera"));
	line_of_sight = cast_to<RayCast>(camera->get_node("RayCast"));
	held_body = NULL;
}

void Player::_physics_process(float delta)
{

	get_input(delta);

}

void Player::_unhandled_input(InputEvent* ev)
{
	auto* mouse = cast_to<InputEventMouseMotion>(ev);
	if (mouse != NULL)
	{
		rotate_head(mouse);

	}
	auto* mouseclick = cast_to<InputEventMouseButton>(ev);
	if (mouseclick != NULL && mouseclick->is_pressed())
	{
		look();
	}

}

void Player::rotate_head(InputEventMouseMotion* mouse)
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
	velocity.y += gravity * delta;
	Vector3 temp_velocity = velocity;
	temp_velocity.y = 0;

	float speed = max_speed;
	if (input->is_action_just_pressed("shift"))
		speed = max_running_speed;

	Vector3 target = direction * speed;

	float acceleration = deaccel;
	if (direction.dot(temp_velocity) > 0)
		acceleration = accel;

	temp_velocity = temp_velocity.linear_interpolate(target, acceleration * delta);
	velocity.x = temp_velocity.x;
	velocity.z = temp_velocity.z;
	velocity = move_and_slide(velocity, Vector3(0, 1, 0));

	if (is_on_floor() && input->is_action_just_pressed("ui_select"))
		velocity.y = jump_height;

	if(input->is_action_just_pressed("grab"))
	{
		pickup();
	}
	if(held_body != NULL)
	{
		Godot::print("moving held body");
		held_body->get_global_transform().set_origin(camera->get_global_transform().get_origin());
	}
}

void Player::look()
{
	if (line_of_sight->is_colliding())
	{
		PhysicsBody* body = cast_to<PhysicsBody>(line_of_sight->get_collider());

		//body->queue_free();
	}
	auto* anim = cast_to<AnimationPlayer>(get_node("Gun")->get_node("AnimationPlayer"));
	anim->play("fire");
}

void Player::pickup()
{
	if(line_of_sight->is_colliding())
	{
		held_body = cast_to<Pickable>(line_of_sight->get_collider());
		ERR_FAIL_COND(held_body == nullptr);
		if(held_body != NULL && held_body->has_method("pick_up"))
		{
			held_body->pick_up(this); 
		}
	}
}
