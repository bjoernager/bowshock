// Copyright 2022-2023 Gabriel Jensen.

#pragma once

#include <bow/bs.h>

#include <GLFW/glfw3.h>

struct bow_impl_gfxdat {
	GLFWwindow * win;
	int          frmbufw;
	int          frmbufh;
};

void bow_drw(    bow_gfxdat * gfxdat,bow_objroot * sys,bow_objroot * objs);
void bow_initgfx(bow_gfxdat * dat);
