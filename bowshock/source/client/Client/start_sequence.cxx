// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>

#include <GLFW/glfw3.h>
#include <string>

using namespace ::std::literals::string_literals;

auto bow::Client::start_sequence() -> bool {
	::bow::log("client"s, "starting start sequence"s);

	auto exit = false;

	constexpr ::GLfloat bowshock_red   = 0x1.6D6D6D6Ep-1f;
	constexpr ::GLfloat bowshock_green = 0x1.81818182p-4f;
	constexpr ::GLfloat bowshock_blue  = 0x1.9999999Ap-3f;

	::glfwSetTime(0x0p0);
	for (double duration = 0x0p0; duration <= 0x3p0; duration = ::glfwGetTime()) {
		if (poll_events()) [[unlikely]] break;

		glClearColor(bowshock_red, bowshock_green, bowshock_blue, 0x1p0);
		glClear(GL_COLOR_BUFFER_BIT);
		::glfwSwapBuffers(renderer.window);
	}

	double const fade_duration = 0x1p0;
	::glfwSetTime(0x0p0);
	for (double factor = 0x0p0; factor <= fade_duration; factor = ::glfwGetTime()) {
		if (poll_events()) [[unlikely]] { break; }

		::GLfloat const red   = bowshock_red   * (0x1p0f - static_cast<::GLfloat>(factor) / static_cast<::GLfloat>(fade_duration));
		::GLfloat const green = bowshock_green * (0x1p0f - static_cast<::GLfloat>(factor) / static_cast<::GLfloat>(fade_duration));
		::GLfloat const blue  = bowshock_blue  * (0x1p0f - static_cast<::GLfloat>(factor) / static_cast<::GLfloat>(fade_duration));

		glClearColor(red, green, blue, 0x1p0);
		glClear(GL_COLOR_BUFFER_BIT);
		::glfwSwapBuffers(renderer.window);
	}

	glClearColor(0x0p0f, 0x0p0f, 0x0p0f, 0x1p0f);
	glClear(GL_COLOR_BUFFER_BIT);
	::glfwSwapBuffers(renderer.window);

	if (::glfwWindowShouldClose(renderer.window)) [[unlikely]] { exit = true; }

	return exit;
}
