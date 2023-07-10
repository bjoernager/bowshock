// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#include <bow/application.hxx>
#include <bow/logic.hxx>

#include <cmath>
#include <cstdio>
#include <fmt/core.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

auto ::bow::Application::loop() noexcept -> void {
	::fmt::print(stderr, "entering main loop\n");

	::GLfloat vertices[] = {
		-0x1.0000p0f, +0x1.0000p0f, 0x0p0f,
		+0x1.0000p0f, +0x1.0000p0f, 0x0p0f,
		+0x0.0000p0f, +0x0.0000p0f, 0x0p0f,
	};

	::GLuint vao;
	::GLuint vbo;
	glGenVertexArrays(0x1, &vao);
	glGenBuffers(0x1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STREAM_DRAW);

	glVertexAttribPointer(0x0, 0x3, GL_FLOAT, GL_FALSE, 0x3* sizeof (::GLfloat), nullptr);
	glEnableVertexAttribArray(0x0);

	// For stellar bodies:
	::bow::ObjectRoot system_root;
	// For miscellaneous objects (canisters,  shps...):
	::bow::ObjectRoot objects_root = {
		.objects = nullptr,
	};

	try {::bow::generate_system(system_root, player_data.system_identifier, player_data.time); }
	catch (::std::bad_alloc const&) {
		::fmt::print(stderr, "unable to allocate memory for object\n");

		::std::abort();
	}

	::bow::Object object_temporary = {
		.type                = ::bow::ObjectType::Canister,
		.canister_content    = ::bow::Ware::Biowaste,
		.position            = {
			.x = 0x0p0,
			.y = -0x2p0,
			.z = 0x0p0,
		},
		.rotation            = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.positional_velocity = {
			.x = -0x1p-12,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.rotational_velocity = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.mass                = 0x1p0,
		.next                = nullptr,
	};
	::bow::add_object(objects_root, object_temporary);

	auto const scroll_handler = [](::GLFWwindow* const window, [[maybe_unused]] double const x_offset, double const y_offset) -> void {
		::bow::PlayerData* data = static_cast<::bow::PlayerData*>(::glfwGetWindowUserPointer(window));

		data->zoom *= ::std::pow(0x1.04p0f, 0x0p0f-static_cast<float>(y_offset));
	};

	::glfwSetWindowUserPointer(graphics_data.window, &player_data);
	::glfwSetScrollCallback(graphics_data.window, scroll_handler);

	for (;; ++player_data.time) {
		if (this->poll_events()) [[unlikely]] break;

		::bow::gravitate(system_root);
		::bow::gravitate(objects_root, system_root);

		::bow::move(system_root);
		::bow::move(objects_root);

		::GLfloat const frame = 0x1p0f*player_data.zoom;

		vertices[0x0u] = static_cast<::GLfloat>(system_root.objects->next->position.x) / frame;
		vertices[0x1u] = static_cast<::GLfloat>(system_root.objects->next->position.y) / frame;
		vertices[0x3u] = static_cast<::GLfloat>(system_root.objects->position.x) / frame;
		vertices[0x4u] = static_cast<::GLfloat>(system_root.objects->position.y) / frame;
		vertices[0x6u] = static_cast<::GLfloat>(objects_root.objects->position.x) / frame;
		vertices[0x7u] = static_cast<::GLfloat>(objects_root.objects->position.y) / frame;

		glClearColor(0x0p0f, 0x0p0f, 0x0p0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0x0, sizeof (vertices), vertices);

		glUseProgram(graphics_data.shader_program);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0x0, 0x3* 0x1);

		::glfwSwapBuffers(graphics_data.window);
	}

	::bow::delete_objects(objects_root);
	::bow::delete_objects(system_root);

	::glfwSetScrollCallback(graphics_data.window, nullptr);

	glDeleteVertexArrays(0x1, &vao);
	glDeleteBuffers(0x1, &vbo);
}
