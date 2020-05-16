#include "Pickable.h"

void Pickable::_register_methods()
{
    register_method("_process", &Pickable::_process);
    register_method("_ready", &Pickable::_ready);

}

Pickable::Pickable()
{

}

Pickable::~Pickable()
{

}

void Pickable::_init()
{

}

void Pickable::_ready()
{

}
void Pickable::_process(float delta)
{
    if(picked_up)
    {
        Spatial *pickup_pos_node = cast_to<Spatial>(holder->get_node("pickup_pos"));
        set_global_transform(pickup_pos_node->get_global_transform());
    }
}

void Pickable::pick_up(Player* player)
{
    holder = player;
    if(picked_up)
    {
        drop();
    }
    else
    {
        carry();
    }
    
}

void Pickable::carry()
{
    auto *collision_shape = cast_to<CollisionShape>(get_node("pickup_pos"));
    collision_shape->set_disabled(true);
    holder->set_pickable(this);
    set_mode(1);
    picked_up = true;
}

void Pickable::drop()
{
    auto *collision_shape = cast_to<CollisionShape>(get_node("pickup_pos"));
    collision_shape->set_disabled(false);
    holder->set_pickable(NULL);
    set_mode(0);
    picked_up = false;

}

void Pickable::throw_item(float power)
{
    //pass
}