// Copyright 2022-2023 Gabriel Jensen.

#include <bow/ini.hxx>

#include <cstdlib>
#include <ctime>

auto ::bow::bow::inirnd() noexcept -> void {
	bow_log("initialising random number generator");
	
	::std::srand(static_cast<unsigned int>(::std::time(nullptr)));
}
