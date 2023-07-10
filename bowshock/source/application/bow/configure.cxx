// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>

#include <cstdio>
#include <cstring>
#include <fmt/core.h>
#include <string>
#include <vector>

using namespace ::std::literals::string_literals;

auto ::bow::Application::configure(::bow::Configuration& configuration, int const argc, char const* const* argv) noexcept -> void {
	::std::string const program_name = *argv;

	configuration = ::bow::Configuration {
		.save_path     = ""s,
		.has_save_path = false,
		.new_save      = false,
		.skip_intro    = false,
	};

	if (argc >= 0x2) [[unlikely]] {
		::std::vector<char const*> parameters(argv + 0x1u, argv + static_cast<::std::size_t>(argc));

		for (auto parameter : parameters) {
			if (parameter[0x0u] == '-' && parameter[0x1u] == '-') {
				parameter += 0x2u;

				     if (!::std::strcmp(parameter, "credits"))    { print_credits(); }
				else if (!::std::strcmp(parameter, "print_help")) { print_help(program_name); }
				else if (!::std::strcmp(parameter, "new"))        { configuration.new_save  = true; }
				else if (!::std::strcmp(parameter, "skip"))       { configuration.skip_intro = true; }
				else                                              { ::fmt::print(stderr, "invalid pareter \"{}\"\n", parameter); }

				continue;
			}

			// Else: Interpret it as a save path.
			configuration.save_path     = parameter;
			configuration.has_save_path = true;
		}
	}
}
