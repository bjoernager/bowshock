// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>

#include <cstdlib>
#include <GLFW/glfw3.h>

void ::bow::bow::quit(::bow::stat const stat) noexcept {
	bow_log("quitting");
	
	glDeleteProgram(gfxDat.shdProg);

	::glfwDestroyWindow(gfxDat.win);
	::glfwTerminate();
	
	int sysstat;
	switch (stat) {
	case ::bow::stat::err:
		sysstat = EXIT_FAILURE;
		break;
	case ::bow::stat::ok:
		sysstat = EXIT_SUCCESS;
		break;
	}

	bow_log("goodbye");
	bow_log("exiting with code %i",sysstat);
	::std::exit(sysstat);
}
