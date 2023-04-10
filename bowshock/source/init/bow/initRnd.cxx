// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>

#include <cstdlib>
#include <ctime>

void ::bow::bow::initRnd() noexcept {
	bow_log("initialising random number generator");
	
	::std::srand(static_cast<unsigned int>(::std::time(nullptr)));
}
