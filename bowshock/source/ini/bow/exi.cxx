// Copyright 2022-2023 Gabriel Jensen.

#include <bow/ini.hxx>

#include <cstdlib>
#include <GLFW/glfw3.h>

auto ::bow::bow::exi(::bow::cnd const cnd) noexcept -> void {
	bow_log("quitting");
	
	glDeleteProgram(gfxdat.shdprg);

	::glfwDestroyWindow(gfxdat.win);
	::glfwTerminate();
	
	int cod;
	switch (cnd) {
	case ::bow::cnd::err:
		cod = EXIT_FAILURE;
		break;
	case ::bow::cnd::oky:
		cod = EXIT_SUCCESS;
		break;
	}

	bow_log("goodbye");
	bow_log("exiting with code %i",cod);
	::std::exit(cod);
}
