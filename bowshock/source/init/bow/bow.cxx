// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>
#include <bow/lgc.hxx>
#include <bow/run.hxx>
#include <bow/sav.hxx>

#include <cinttypes>

::bow::bow::bow(int const argc,char const * const * const argv) noexcept {
	init(argc,argv);
}

::bow::bow::~bow() noexcept {
	quit(::bow::stat::ok);
}

int main(int const argc,char const * const * argv) {
	::bow::bow bow = {argc,argv};
}
