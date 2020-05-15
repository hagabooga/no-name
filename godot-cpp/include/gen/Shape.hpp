#ifndef GODOT_CPP_SHAPE_HPP
#define GODOT_CPP_SHAPE_HPP


#include <gdnative_api_struct.gen.h>
#include <stdint.h>

#include <core/CoreTypes.hpp>
#include <core/Ref.hpp>

#include "Resource.hpp"
namespace godot {


class Shape : public Resource {
	struct ___method_bindings {
		godot_method_bind *mb_get_margin;
		godot_method_bind *mb_set_margin;
	};
	static ___method_bindings ___mb;

public:
	static void ___init_method_bindings();

	static inline const char *___get_class_name() { return (const char *) "Shape"; }
	static inline Object *___get_from_variant(Variant a) { godot_object *o = (godot_object*) a; return (o) ? (Object *) godot::nativescript_1_1_api->godot_nativescript_get_instance_binding_data(godot::_RegisterState::language_index, o) : nullptr; }

	// enums

	// constants

	// methods
	real_t get_margin() const;
	void set_margin(const real_t margin);

};

}

#endif