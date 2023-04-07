// Copyright 2022-2023 Gabriel Jensen.

#pragma once

#include <bow/bs.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <signal.h>

typedef struct {
	GLFWwindow * win;
	GLuint       shdProg;
} bow_gfxDat;

extern sig_atomic_t volatile bow_gotIntr;

[[noreturn]] void bow_abrt(void);
[[noreturn]] void bow_quit(bow_gfxDat * gfxdat,bow_stat stat);

bow_obj * bow_addObj(  bow_objRoot * root,bow_obj const * obj);
void      bow_freeObjs(bow_objRoot * root);

void bow_genSys(bow_objRoot * sys,zap_i04 id,zap_i04 tm);

bool bow_pollEvts(bow_gfxDat * const gfxdat);

void bow_drw(bow_gfxDat * gfxdat,bow_objRoot * sys,bow_objRoot * objs,float zoom);

bool bow_intro(bow_gfxDat * gfxdat);
void bow_loop( bow_gfxDat * gfxdat,bow_plDat * pldat);
