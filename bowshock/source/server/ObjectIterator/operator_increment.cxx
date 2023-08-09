// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>

auto bow::ObjectIterator::operator ++() noexcept -> ::bow::ObjectIterator& {
	this->element = this->element->next;

	return *this;
}
