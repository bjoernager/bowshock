// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/server.hxx>

auto bow::ObjectRoot::begin() const noexcept -> ::bow::ObjectIterator {
	return ::bow::ObjectIterator(*this);
}
