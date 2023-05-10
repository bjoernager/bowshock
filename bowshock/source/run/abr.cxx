// Copyright 2022-2023 Gabriel Jensen.

#include <bow/run.hxx>

#include <cinttypes>
#include <cstdlib>
#include <source_location>

auto ::bow::abr(::std::source_location const srcloc) noexcept -> void {
	bow_log("\x1B[38;5;197maborting\x1B[0m from \"%s\":%" PRIXLEAST32 " @ %s\n",srcloc.file_name(),srcloc.line(),srcloc.function_name());
	
	::std::abort();
}
