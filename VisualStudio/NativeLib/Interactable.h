#pragma once

#include "Common.h"
#include <RigidBody.hpp>
#include <CollisionShape.hpp>
#include <MeshInstance.hpp>


class Interactable : public RigidBody
{
	GODOT_CLASS(Interactable, RigidBody);

private:


protected:
	CollisionShape* collision_shape;

public:
	static void _register_methods();

	Interactable();
	~Interactable();

	virtual void _init();
	virtual void _ready();

	virtual void interact() = 0;


};