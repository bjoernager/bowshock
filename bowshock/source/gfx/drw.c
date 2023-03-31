// Copyright 2022-2023 Gabriel Jensen.

#include <bow/gfx.h>
#include <bow/lgc.h>

#include <GLFW/glfw3.h>

static void bow_drwobjs(bow_objroot * const root,float const zoom) {
	float const frm = 0x1p0*zoom;
	for (bow_obj * obj = root->objs;obj != nullptr;obj = obj->next) {
		GLfloat const posx = (GLfloat)obj->pos.x/frm;
		GLfloat const posy = (GLfloat)obj->pos.y/frm;
		GLfloat const posz = (GLfloat)obj->pos.z/frm;
		glVertex3f(posx,posy,posz);
	}
}

void bow_drw(bow_gfxdat * gfxdat,bow_objroot * const sys,bow_objroot * const objs,float const zoom) {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(0x2p0);
	glBegin(GL_POINTS);
	bow_drwobjs(sys,zoom);
	bow_drwobjs(objs,zoom);
	glEnd();
	glfwSwapBuffers(gfxdat->win);
}
