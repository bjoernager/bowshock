// Copyright 2022-2023 Gabriel Jensen.

#include <bow/run.hxx>

#include <cstdlib>

void ::bow::abrt() noexcept {
	bow_log("\x1B[38;5;197maborting\x1B[0m");
	
	::std::abort();
}
