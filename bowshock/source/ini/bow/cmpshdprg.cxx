// Copyright 2022-2023 Gabriel Jensen.

#include <bow/ini.hxx>

#include <glad/glad.h>
#include <stdexcept>

auto ::bow::bow::compshdprog(::GLuint & shdprog,char const * const nam) noexcept -> void {
	bow_log("compiling shader program \"%s\"",nam);

	::GLuint vtxshd;
	::GLuint frgshd;

	try {
		cmpshd(vtxshd,nam,GL_VERTEX_SHADER);
		cmpshd(frgshd,nam,GL_FRAGMENT_SHADER);
	}
	catch (::std::runtime_error const & e) {
		bow_logerr("%s",e.what());
		::bow::abr();
	}
	catch (::std::bad_alloc const & e) {
		bow_logerr("unable to allocate memory for shader data");
		::bow::abr();
	}

	shdprog = glCreateProgram();
	glAttachShader(shdprog,vtxshd);
	glAttachShader(shdprog,frgshd);
	glLinkProgram(shdprog);

	glDeleteShader(vtxshd);
	glDeleteShader(frgshd);
}
