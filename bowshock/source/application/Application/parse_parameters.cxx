// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>
#include <bow/client.hxx>
#include <bow/network.hxx>

#include <charconv>
#include <format>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

using namespace ::std::literals::string_literals;

auto bow::Application::parse_parameters(::std::string const& program_name, ::std::vector<char const*> const& parameters) -> void {
	::bow::log("app"s, "parsing parameters"s);

	if (parameters.size() >= 0x1u) [[unlikely]] {
		auto const parse = [&program_name, this](::std::string const& parameter) -> void {
			if (auto const offset = parameter.find("="); offset != ::std::string::npos) {
				auto const field = ::std::string_view(parameter.begin(), parameter.begin() + offset);
				auto const value = ::std::string_view(parameter.begin() + offset + 0x1u, parameter.end());

				if (field == "directory"s) {
					::bow::log("app"s, ::std::format("setting directory to \"{}\"", value));
					this->client_configuration.directory = value;
				} else if (field == "port"s) {
					auto const numeric_value = [&field, &value]() -> ::std::uint16_t {
						::std::uint_least16_t numeric_value = UINT16_C(0x0);

						auto const result = ::std::from_chars(value.begin(), value.end(), numeric_value);

						bool const out_of_range =
						   result.ec == ::std::errc::result_out_of_range
						|| numeric_value < ::bow::MINIMUM_NETWORK_PORT
						|| numeric_value > ::bow::MAXIMUM_NETWORK_PORT;

						if (out_of_range) [[unlikely]] {
							::bow::log("app"s, ::std::format("value ({}) for {} is out of range (min. is {}, max. is {})", value, field, ::bow::MINIMUM_NETWORK_PORT, ::bow::MAXIMUM_NETWORK_PORT));
							throw ::std::invalid_argument("value out of range"s);
						}

						if (result.ec != ::std::errc()) [[unlikely]] {
							::bow::log("app"s, ::std::format("invalid value ({}) for {}", value, field));
							throw ::std::invalid_argument("invalid value"s);
						}

						return numeric_value;
					}();

					::bow::log("app"s, ::std::format("setting the port number to {}", numeric_value));
					this->client_configuration.network_port = numeric_value;
					this->server_configuration.network_port = numeric_value;
				} else if (field == "save"s) {
					::bow::log("app"s, ::std::format("setting save name to \"{}\"", value));
					this->client_configuration.save_name = value;
				} else {
					throw ::std::invalid_argument(::std::format("invalid field name \"{}\"", field));
				}
			} else {
				auto const flag = ::std::string_view(parameter.begin(), parameter.end());

				if (flag == "credits"s) {
					::bow::Application::print_credits();
				} else if (flag == "help") {
					::bow::Application::print_help(program_name);
				} else if (flag == "new") {
					::bow::log("app"s, "using default save file"s);
					this->client_configuration.new_save = true;
				} else if (flag == "skip") {
					::bow::log("app"s, "skipping start sequence"s);
					this->client_configuration.skip_start_sequence = true;
				} else {
					throw ::std::invalid_argument(::std::format("invalid flag \"{}\"", flag));
				}
			}
		};

		for (auto const parameter: parameters) {
			parse(parameter);
		}
	}
}
