#ifndef GODOT_CPP_VISUALSHADERNODESCALARCONSTANT_HPP
#define GODOT_CPP_VISUALSHADERNODESCALARCONSTANT_HPP


#include <gdnative_api_struct.gen.h>
#include <stdint.h>

#include <core/CoreTypes.hpp>
#include <core/Ref.hpp>

#include "VisualShaderNode.hpp"
namespace godot {


class VisualShaderNodeScalarConstant : public VisualShaderNode {
	struct ___method_bindings {
		godot_method_bind *mb_get_constant;
		godot_method_bind *mb_set_constant;
	};
	static ___method_bindings ___mb;

public:
	static void ___init_method_bindings();

	static inline const char *___get_class_name() { return (const char *) "VisualShaderNodeScalarConstant"; }
	static inline Object *___get_from_variant(Variant a) { godot_object *o = (godot_object*) a; return (o) ? (Object *) godot::nativescript_1_1_api->godot_nativescript_get_instance_binding_data(godot::_RegisterState::language_index, o) : nullptr; }

	// enums

	// constants


	static VisualShaderNodeScalarConstant *_new();

	// methods
	real_t get_constant() const;
	void set_constant(const real_t value);

};

}

#endif