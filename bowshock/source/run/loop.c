// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.h>
#include <bow/run.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <math.h>
#include <zap/mem.h>

static void bow_scrlHand(GLFWwindow * win,[[maybe_unused]] double const xoff,double const yoff) {
	bow_plDat * dat = glfwGetWindowUserPointer(win);
	dat->zoom *= powf(0x1.1p0f,0x0p0f-(float)yoff);
}

void bow_loop(bow_gfxDat * gfxDatPtr,bow_plDat * plDatPtr) {
	bow_log("entering main loop");
	
	bow_gfxDat gfxDat;
	bow_plDat  plDat;
	zap_cp(&gfxDat, gfxDatPtr, sizeof (gfxDat));
	zap_cp(&plDat,plDatPtr,sizeof (plDat));
	
	GLfloat vtx[] = {
		-0x1.0000p0f,+0x1.0000p0f,0x0p0f,
		+0x1.0000p0f,+0x1.0000p0f,0x0p0f,
		+0x0.0000p0f,+0x0.0000p0f,0x0p0f,
	};

	GLuint vao;
	GLuint vbo;
	glGenVertexArrays(0x1,&vao);
	glGenBuffers(0x1,&vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof (vtx),vtx,GL_STREAM_DRAW);

	glVertexAttribPointer(0x0,0x3,GL_FLOAT,GL_FALSE,0x3 * sizeof (GLfloat),nullptr);
	glEnableVertexAttribArray(0x0);

	bow_objRoot sysRoot; // For stellar bodies.
	bow_objRoot objRoot = { // For miscellaneous objects (canisters, ships...).
		.objs = nullptr,
	};

	bow_genSys(&sysRoot,plDat.sysId,plDat.tm);

	bow_obj objTmp = {
		.typ     = bow_objTyp_can,
		.pos     = {
			.x = 0x0p0,
			.y = -0x2p0,
			.z = 0x0p0,
		},
		.rot     = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.posVel  = {
			.x = -0x1p-12,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.rotVel  = {
			.x = 0x0p0,
			.y = 0x0p0,
			.z = 0x0p0,
		},
		.mass    = 0x1p0,
	};
	bow_addObj(&objRoot,&objTmp);

	glfwSetWindowUserPointer(gfxDat.win,&plDat);
	glfwSetScrollCallback(gfxDat.win,bow_scrlHand);

	for (;;++plDat.tm) {
		unlikely (bow_pollEvts(&gfxDat)) break;

		bow_gravSys(&sysRoot);
		bow_gravObjs(&objRoot,&sysRoot);

		bow_mvObjs(&sysRoot);
		bow_mvObjs(&objRoot);

		GLfloat const frm = 0x1p0*plDat.zoom;

		vtx[0x0u] = (GLfloat)sysRoot.objs->next->pos.x/frm;
		vtx[0x1u] = (GLfloat)sysRoot.objs->next->pos.y/frm;
		vtx[0x3u] = (GLfloat)sysRoot.objs->pos.x/frm;
		vtx[0x4u] = (GLfloat)sysRoot.objs->pos.y/frm;
		vtx[0x6u] = (GLfloat)objRoot.objs->pos.x/frm;
		vtx[0x7u] = (GLfloat)objRoot.objs->pos.y/frm;

		glClearColor(0x0p0f,0x0p0f,0x0p0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindBuffer(GL_ARRAY_BUFFER,vbo);
		glBufferSubData(GL_ARRAY_BUFFER,0x0,sizeof (vtx),vtx);

		glUseProgram(gfxDat.shdProg);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES,0x0,0x3 * 0x1);

		glfwSwapBuffers(gfxDat.win);
	}

	glfwSetScrollCallback(gfxDat.win,nullptr);

	glDeleteVertexArrays(0x1,&vao);
	glDeleteBuffers(0x1,&vbo);

	zap_cp(gfxDatPtr,&gfxDat,sizeof (gfxDat));
	zap_cp(plDatPtr, &plDat, sizeof (plDat));
}
