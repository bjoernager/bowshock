// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>

int main(int const argc, char const* const* argv) {
	auto application = ::bow::Application(argc, argv);

	return application.run();
}
