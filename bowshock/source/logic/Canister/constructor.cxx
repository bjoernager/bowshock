// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/logic.hxx>

bow::Canister::Canister() noexcept {
	this->object_type = ::bow::ObjectType::Canister;

	this->position.x            = 0x0p0;
	this->position.y            = 0x0p0;
	this->position.z            = 0x0p0;
	this->rotation.x            = 0x0p0;
	this->rotation.y            = 0x0p0;
	this->rotation.z            = 0x0p0;
	this->positional_velocity.x = 0x0p0;
	this->positional_velocity.y = 0x0p0;
	this->positional_velocity.z = 0x0p0;
	this->rotational_velocity.x = 0x0p0;
	this->rotational_velocity.y = 0x0p0;
	this->rotational_velocity.z = 0x0p0;
	this->mass                  = 0x0p0;
	this->content               = ::bow::Ware::Biowaste;

	this->mass = ::bow::ware_mass(this->content) * 0x1p0;
}
