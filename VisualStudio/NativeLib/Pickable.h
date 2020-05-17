#pragma once
#include "Common.h"
#include <RigidBody.hpp>
#include <CollisionShape.hpp>
class Pickable : public RigidBody
{
    GODOT_CLASS(Pickable, RigidBody);
private:
    bool picked_up = false;
    Spatial *holder;
public:
    static void _register_methods();

    Pickable();
    ~Pickable();

    void _init();
    void _ready();
    
    void _process(float delta);
    void pick_up(Spatial *pickup_pos_node);
    void carry();
    void drop();
    void throw_item(float power);
};