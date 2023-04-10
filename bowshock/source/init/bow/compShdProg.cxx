// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>

#include <glad/glad.h>
#include <stdexcept>

void ::bow::bow::compShdProg(GLuint & shdProg,char const * const nm) noexcept {
	bow_log("compiling shader program \"%s\"",nm);

	GLuint vtxShd;
	GLuint fragShd;

	try {
		compShd(vtxShd, nm, GL_VERTEX_SHADER);
		compShd(fragShd,nm,GL_FRAGMENT_SHADER);
	}
	catch (::std::runtime_error const & e) {
		bow_logErr("%s",e.what());
		::bow::abrt();
	}
	catch (::std::bad_alloc const & e) {
		bow_logErr("unable to allocate memory for shader data");
		::bow::abrt();
	}

	shdProg = glCreateProgram();
	glAttachShader(shdProg,vtxShd);
	glAttachShader(shdProg,fragShd);
	glLinkProgram(shdProg);

	glDeleteShader(vtxShd);
	glDeleteShader(fragShd);
}
