// Copyright 2022-2023 Gabriel Jensen.

#pragma once

#include <bow/bs.hxx>

#include <source_location>

namespace bow {
	[[noreturn]] auto abr(::std::source_location srcloc = ::std::source_location::current()) noexcept -> void;

	auto addobj(::bow::objroot &       root,::bow::obj const & obj)          -> void;
	auto remobj(::bow::objroot const & root)                        noexcept -> void;

	auto gensys(::bow::objroot & sys,::zp::i04 id,::zp::i04 tim) -> void;
}
