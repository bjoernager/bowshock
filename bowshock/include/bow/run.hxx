// Copyright 2022-2023 Gabriel Jensen.

#pragma once

#include <bow/bs.hxx>

namespace bow {
	[[noreturn]] void abrt() noexcept;

	void addObj(  ::bow::objRoot &       root,::bow::obj const & obj);
	void freeObjs(::bow::objRoot const & root)                        noexcept;

	void genSys(::bow::objRoot & sys,::zap::i04 id,::zap::i04 tm);
}