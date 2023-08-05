// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>
#include <bow/client.hxx>

#include <cstdio>
#include <fmt/core.h>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

using namespace ::std::literals::string_literals;

auto bow::Application::parse_parameters(::std::string const& program_name, ::std::vector<char const*> const& parameters) -> void {
	::fmt::print(stderr, "[app] parsing parameters\n");

	if (parameters.size() >= 0x1u) [[unlikely]] {
		auto const parse = [&program_name](::bow::ClientConfiguration& client_configuration, ::std::string const& parameter) -> void {
			if (auto const offset = parameter.find("="); offset != ::std::string::npos) {
				auto const field = ::std::string_view(parameter.begin(), parameter.begin() + offset);
				auto const value = ::std::string_view(parameter.begin() + offset + 0x1u, parameter.end());

				if (field == "directory") {
					::fmt::print(stderr, "[app] setting directory to \"{}\"\n", value);

					client_configuration.directory = value;
				} else if (field == "name") {
					::fmt::print(stderr, "[app] setting save name to \"{}\"\n", value);

					client_configuration.save_name = value;
				} else {
					::fmt::print(stderr, "[app] invalid field name \"{}\"\n", field);

					throw ::std::logic_error("invalid field name");
				}
			} else {
				auto const setting = ::std::string_view(parameter.begin(), parameter.end());

				if (setting == "credits") {
					::bow::Application::print_credits();
				} else if (setting == "help") {
					::bow::Application::print_help(program_name);
				} else if (setting == "new") {
					::fmt::print(stderr, "[app] using default save file\n");

					client_configuration.new_save = true;
				} else if (setting == "skip") {
					::fmt::print(stderr, "[app] skipping start sequence\n");

					client_configuration.skip_start_sequence = true;
				} else {
					::fmt::print(stderr, "[app] invalid setting\"{}\"\n", setting);

					throw ::std::logic_error("invalid setting");
				}
			}
		};

		for (auto const parameter : parameters) {
			parse(this->client_configuration, parameter);
		}
	}
}
