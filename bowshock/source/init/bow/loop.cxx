// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>
#include <bow/lgc.hxx>

#include <GLFW/glfw3.h>
#include <cmath>
#include <glad/glad.h>
#include <stdexcept>

void ::bow::bow::loop() noexcept {
	bow_log("entering main loop");
	
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

	::bow::objRoot sysRoot; // For stellar bodies.
	::bow::objRoot objRoot = { // For miscellaneous objects (canisters, ships...).
		.objs = nullptr,
	};

	try {::bow::genSys(sysRoot,plDat.sysId,plDat.tm);}
	catch (::std::bad_alloc const & e) {
		bow_logErr("unable to allocate memory for object");
		::bow::abrt();
	}

	::bow::obj objTmp = {
		.typ     = ::bow::objTyp::can,
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
	::bow::addObj(objRoot,objTmp);

	auto const scrlHand = [](::GLFWwindow * const win,[[maybe_unused]] double const xoff,double const yoff) -> void {
		::bow::plDat * dat = static_cast<::bow::plDat *>(::glfwGetWindowUserPointer(win));
		dat->zoom *= ::std::pow(0x1.04p0f,0x0p0f-static_cast<float>(yoff));
	};

	::glfwSetWindowUserPointer(gfxDat.win,&plDat);
	::glfwSetScrollCallback(gfxDat.win,scrlHand);

	for (;;++plDat.tm) {
		if (pollEvts()) [[unlikely]] break;

		::bow::grav(sysRoot);
		::bow::grav(objRoot,sysRoot);

		::bow::mv(sysRoot);
		::bow::mv(objRoot);

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

		::glfwSwapBuffers(gfxDat.win);
	}

	::glfwSetScrollCallback(gfxDat.win,nullptr);

	glDeleteVertexArrays(0x1,&vao);
	glDeleteBuffers(0x1,&vbo);
}
