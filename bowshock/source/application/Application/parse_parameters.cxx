// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>
#include <bow/client.hxx>
#include <bow/network.hxx>

#include <charconv>
#include <cstdio>
#include <fmt/core.h>
#include <format>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

using namespace ::std::literals::string_literals;

auto bow::Application::parse_parameters(::std::string const& program_name, ::std::vector<char const*> const& parameters) -> void {
	::fmt::print(stderr, "[app] parsing parameters\n");

	if (parameters.size() >= 0x1u) [[unlikely]] {
		auto const parse = [&program_name, this](::std::string const& parameter) -> void {
			if (auto const offset = parameter.find("="); offset != ::std::string::npos) {
				auto const field = ::std::string_view(parameter.begin(), parameter.begin() + offset);
				auto const value = ::std::string_view(parameter.begin() + offset + 0x1u, parameter.end());

				if (field == "directory") {
					::fmt::print(stderr, "[app] setting directory to \"{}\"\n", value);
					this->client_configuration.directory = value;
				} else if (field == "port") {
					auto const numeric_value = [&field, &value]() -> ::std::uint16_t {
						::std::uint_least16_t numeric_value = UINT16_C(0x0);

						auto const result = ::std::from_chars(value.begin(), value.end(), numeric_value);

						bool const out_of_range =
						   result.ec == ::std::errc::result_out_of_range
						|| numeric_value < ::bow::MINIMUM_NETWORK_PORT
						|| numeric_value > ::bow::MAXIMUM_NETWORK_PORT;

						if (out_of_range) [[unlikely]] {
							::fmt::print(stderr, "[app] value ({}) for {} is out of range (min. is {}, max. is {})\n", value, field, ::bow::MINIMUM_NETWORK_PORT, ::bow::MAXIMUM_NETWORK_PORT);
							throw ::std::invalid_argument("value out of range");
						}

						if (result.ec != ::std::errc()) [[unlikely]] {
							::fmt::print(stderr, "[app] invalid value ({}) for {}\n", value, field);
							throw ::std::invalid_argument("invalid value");
						}

						return numeric_value;
					}();

					::fmt::print(stderr, "[app] setting the port number to {}\n", numeric_value);
					this->client_configuration.network_port = numeric_value;
					this->server_configuration.network_port = numeric_value;
				} else if (field == "save") {
					::fmt::print(stderr, "[app] setting save name to \"{}\"\n", value);
					this->client_configuration.save_name = value;
				} else {
					throw ::std::invalid_argument(::std::format("invalid field name \"{}\"", field));
				}
			} else {
				auto const setting = ::std::string_view(parameter.begin(), parameter.end());

				if (setting == "credits") {
					::bow::Application::print_credits();
				} else if (setting == "help") {
					::bow::Application::print_help(program_name);
				} else if (setting == "new") {
					::fmt::print(stderr, "[app] using default save file\n");
					this->client_configuration.new_save = true;
				} else if (setting == "skip") {
					::fmt::print(stderr, "[app] skipping start sequence\n");
					this->client_configuration.skip_start_sequence = true;
				} else {
					::fmt::print(stderr, "[app] invalid setting\"{}\"\n", setting);
					throw ::std::invalid_argument("invalid setting");
				}
			}
		};

		for (auto const parameter: parameters) {
			parse(parameter);
		}
	}
}
