// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fmt/core.h>
#include <string>

auto ::bow::Application::print_quote() noexcept -> void {
	::std::srand(static_cast<unsigned int>(::std::time(nullptr)));

	auto const identifier = static_cast<::std::uint8_t>(rand()) % ::bow::NUMBER_OF_QUOTE_IDENTIFIERS;

	::std::string quote;
	::std::string source;
	get_quote(quote, source, identifier);

	::fmt::print(stderr, "{}\n\u2014{}\n\n", quote, source);
}
