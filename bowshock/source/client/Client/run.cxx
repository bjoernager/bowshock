// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/client.hxx>
#include <bow/logic.hxx>

#include <cmath>
#include <cstdio>
#include <fmt/core.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

auto bow::Client::run() noexcept -> void {
	::fmt::print(stderr, "[client] running\n");

	if (!this->configuration.skip_start_sequence && start_sequence()) [[unlikely]] { return; }

	::fmt::print(stderr, "[client] entering main loop\n");

	::GLfloat vertices[] = {
		-0x1.0000p0f, +0x1.0000p0f, 0x0p0f,
		+0x1.0000p0f, +0x1.0000p0f, 0x0p0f,
		+0x0.0000p0f, +0x0.0000p0f, 0x0p0f,
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STREAM_DRAW);

	glVertexAttribPointer(0x0, 0x3, GL_FLOAT, GL_FALSE, 0x3* sizeof (::GLfloat), nullptr);
	glEnableVertexAttribArray(0x0);

	auto const scroll_handler = [](::GLFWwindow* const window, [[maybe_unused]] double const horizontal_offset, double const vertical_offset) -> void {
		auto const data = static_cast<::bow::PlayerData*>(::glfwGetWindowUserPointer(window));

		data->zoom *= ::std::pow(0x1.04p0f, -static_cast<float>(vertical_offset));
	};

	::glfwSetWindowUserPointer(this->renderer.window, &player_data);
	::glfwSetScrollCallback(this->renderer.window, scroll_handler);

	for (;;) {
		if (this->poll_events()) [[unlikely]] { break; }

		::GLfloat const frame = 0x1p0f * player_data.zoom;

		// Currently, we don't recieve any information from
		// the server.

		//vertices[0x0] = static_cast<::GLfloat>(system_root.objects->next->position.x) / frame;
		//vertices[0x1] = static_cast<::GLfloat>(system_root.objects->next->position.y) / frame;
		//vertices[0x3] = static_cast<::GLfloat>(system_root.objects->position.x) / frame;
		//vertices[0x4] = static_cast<::GLfloat>(system_root.objects->position.y) / frame;
		//vertices[0x6] = static_cast<::GLfloat>(objects_root.objects->position.x) / frame;
		//vertices[0x7] = static_cast<::GLfloat>(objects_root.objects->position.y) / frame;

		this->renderer.render(vertices, sizeof (vertices));
	}

	::glfwSetScrollCallback(this->renderer.window, nullptr);

	glDeleteVertexArrays(0x1, &this->renderer.vao);
	glDeleteBuffers(0x1, &this->renderer.vbo);

	this->player_data.save(::bow::Client::save_path(this->configuration.directory, this->configuration.save_name));

}
