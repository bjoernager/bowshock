// Copyright 2022-2023 Gabriel Jensen.

#include <bow/gfx.h>
#include <bow/lgc.h>

#include <GLFW/glfw3.h>
#include <zap/mem.h>

static void bow_drwobjs(bow_objroot * const root) {
	double const frm = 0x22'3F8B'93C0p0*0x6p0;
	for (bow_obj * obj = root->objs;obj != nullptr;obj = obj->next) {
		GLfloat const posx = (GLfloat)obj->pos.x/frm;
		GLfloat const posy = (GLfloat)obj->pos.y/frm;
		GLfloat const posz = (GLfloat)obj->pos.z/frm;
		glColor3f(0x1p0,0x1p0,0x1p0);
		glVertex3f(posx,posy,posz);
	}
}

void bow_drw(bow_gfxdat * gfxdatptr,bow_objroot * const sys,bow_objroot * const objs) {
	bow_gfxdat gfxdat;
	zap_cp(&gfxdat,gfxdatptr,sizeof (gfxdat));
	int frmbufw;
	int frmbufh;
	glfwGetFramebufferSize(gfxdat.win,&frmbufw,&frmbufh);
	glViewport(0x0,0x0,frmbufw,frmbufh);
	glOrtho(-0x1p0,0x1p0,-0x1p0,0x1p0,0x0p0,0x0p0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(0x4p0);
	glBegin(GL_POINTS);
	bow_drwobjs(sys);
	bow_drwobjs(objs);
	glEnd();
	glfwSwapBuffers(gfxdat.win);
	zap_cp(gfxdatptr,&gfxdat,sizeof (gfxdat));
}
