// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>

auto bow::ObjectRoot::end() const noexcept -> ::bow::ObjectIterator {
	auto iterator =  ::bow::ObjectIterator(*this);

	while (++iterator != nullptr) {}

	return iterator;
}
