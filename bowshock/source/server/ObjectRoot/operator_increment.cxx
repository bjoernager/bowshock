// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>

auto bow::ObjectIterator::operator ++() noexcept -> T& {
	this->object = this->object->next;

	return *this;
}
