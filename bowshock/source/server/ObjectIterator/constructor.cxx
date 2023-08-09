// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>

bow::ObjectIterator::ObjectIterator(::bow::ObjectRoot const& root) noexcept {
	this->element = root.elements;
}
