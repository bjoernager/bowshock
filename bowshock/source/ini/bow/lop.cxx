// Copyright 2022-2023 Gabriel Jensen.

#include <bow/ini.hxx>
#include <bow/lgc.hxx>

#include <GLFW/glfw3.h>
#include <cmath>
#include <glad/glad.h>
#include <stdexcept>

auto ::bow::bow::lop() noexcept -> void {
	bow_log("entering main loop");
	
	::GLfloat vtx[] = {
		-0x1.0000p0f,+0x1.0000p0f,0x0p0f,
		+0x1.0000p0f,+0x1.0000p0f,0x0p0f,
		+0x0.0000p0f,+0x0.0000p0f,0x0p0f,
	};

	::GLuint vao;
	::GLuint vbo;
	glGenVertexArrays(0x1,&vao);
	glGenBuffers(0x1,&vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof (vtx),vtx,GL_STREAM_DRAW);

	glVertexAttribPointer(0x0,0x3,GL_FLOAT,GL_FALSE,0x3 * sizeof (::GLfloat),nullptr);
	glEnableVertexAttribArray(0x0);

	::bow::objroot sysRoot; // For stellar bodies.
	::bow::objroot objroot = { // For miscellaneous objects (canisters, shps...).
		.objs = nullptr,
	};

	try {::bow::gensys(sysRoot,plydat.sysidt,plydat.tim);}
	catch (::std::bad_alloc const & e) {
		bow_logerr("unable to allocate memory for object");
		::bow::abr();
	}

	::bow::obj objTmp = {
		.typ     = ::bow::objtyp::can,
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
		.mas    = 0x1p0,
	};
	::bow::addobj(objroot,objTmp);

	auto const scrlHand = [](::GLFWwindow * const win,[[maybe_unused]] ::zp::f04 const xoff,::zp::f04 const yoff) -> void {
		::bow::plydat * dat = static_cast<::bow::plydat *>(::glfwGetWindowUserPointer(win));
		dat->zom *= ::std::pow(0x1.04p0f,0x0p0f-static_cast<float>(yoff));
	};

	::glfwSetWindowUserPointer(gfxdat.win,&plydat);
	::glfwSetScrollCallback(gfxdat.win,scrlHand);

	for (;;++plydat.tim) {
		if (polevt()) [[unlikely]] break;

		::bow::grv(sysRoot);
		::bow::grv(objroot,sysRoot);

		::bow::mov(sysRoot);
		::bow::mov(objroot);

		::GLfloat const frm = 0x1p0*plydat.zom;

		vtx[0x0u] = (::GLfloat)sysRoot.objs->nxt->pos.x/frm;
		vtx[0x1u] = (::GLfloat)sysRoot.objs->nxt->pos.y/frm;
		vtx[0x3u] = (::GLfloat)sysRoot.objs->pos.x/frm;
		vtx[0x4u] = (::GLfloat)sysRoot.objs->pos.y/frm;
		vtx[0x6u] = (::GLfloat)objroot.objs->pos.x/frm;
		vtx[0x7u] = (::GLfloat)objroot.objs->pos.y/frm;

		glClearColor(0x0p0f,0x0p0f,0x0p0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindBuffer(GL_ARRAY_BUFFER,vbo);
		glBufferSubData(GL_ARRAY_BUFFER,0x0,sizeof (vtx),vtx);

		glUseProgram(gfxdat.shdprg);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES,0x0,0x3 * 0x1);

		::glfwSwapBuffers(gfxdat.win);
	}

	::glfwSetScrollCallback(gfxdat.win,nullptr);

	glDeleteVertexArrays(0x1,&vao);
	glDeleteBuffers(0x1,&vbo);
}
