// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>

#include <cstddef>

auto bow::ObjectIterator::operator ==(::bow::ObjectIterator const& other) const noexcept -> bool {
	return this->element == other.element;
}

auto bow::ObjectIterator::operator ==(::std::nullptr_t) const noexcept -> bool {
	return this->element == nullptr;
}
