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
}

void Player::_physics_process(float delta)
{

	get_input(delta);

}

void Player::_unhandled_input(InputEvent * ev)
{
	auto* mouse = cast_to<InputEventMouseMotion>(ev);
	if (mouse != NULL)
	{
		rotate_y(Helper::deg2rad(-mouse->get_relative().x * mouse_sensitivity));

		float change = -mouse->get_relative().y * mouse_sensitivity;
		if (change + camera_angle < 90.0 && change + camera_angle > -90.0f)
		{
			camera->rotate_x(Helper::deg2rad(change));
			camera_angle += change;
		}
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

	if (input->is_action_just_pressed("ui_select"))
		velocity.y = jump_height;

}
