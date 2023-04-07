// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.h>

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <zap/mem.h>
#include <zap/str.h>

void bow_compShdProg(GLuint * const shdProgPtr,char const * const nm) {
	bow_log("compiling shader program \"%s\"",nm);

	GLuint vtxShd;
	GLuint fragShd;

	bool err = false;

	err |= bow_compShd(&vtxShd, nm, GL_VERTEX_SHADER);
	err |= bow_compShd(&fragShd,nm,GL_FRAGMENT_SHADER);

	if (err) {
		bow_logErr("unable to compile shaders");
		bow_abrt();
	}

	GLuint shdProg = glCreateProgram();
	glAttachShader(shdProg,vtxShd);
	glAttachShader(shdProg,fragShd);
	glLinkProgram(shdProg);

	glDeleteShader(vtxShd);
	glDeleteShader(fragShd);

	*shdProgPtr = shdProg;
}
