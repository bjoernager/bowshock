// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.h>

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <zap/mem.h>
#include <zap/str.h>

#define bow_shdFilExt ("glsl")

bool bow_compShd(GLuint * const refPtr,char const * const nm,GLenum const typ) {
	char const * typStr;
	
	char const * typExt;
	zap_sz       typExtLen;
	switch (typ) {
	default:
		bow_logErr("bad shader type %lX",(unsigned long)typ);
		bow_abrt();
	case GL_FRAGMENT_SHADER:
		bow_setStrLen(typExt,typExtLen,"frag");
		typStr = "fragment";
		break;
	case GL_VERTEX_SHADER:
		bow_setStrLen(typExt,typExtLen,"vert");
		typStr = "vertex";
		break;
	}

	char const * dir;
	zap_sz       dirLen;
	bow_setStrLen(dir,dirLen,bow_datDir "/shaders");

	zap_sz const nmLen     = zap_strlen(nm);
	zap_sz const pthLen    = dirLen + 0x1u + nmLen + 0x1u + typExtLen + 0x1u + sizeof (bow_shdFilExt);

	char * pth = malloc(pthLen + 0x1u);
	if (pth == nullptr) {
		bow_logErr("unable to allocate memory for shader source path");
		bow_abrt();
	}

	pth = zap_cp(pth,dir,dirLen).dest;
	*pth++ = '/';
	pth = zap_cp(pth,nm,nmLen).dest;
	*pth++ = '.';
	pth = zap_cp(pth,typExt,typExtLen).dest;
	*pth++ = '.';
	pth = zap_cp(pth,bow_shdFilExt,sizeof (bow_shdFilExt)).dest;
	*pth   = '\x00';
	pth -= pthLen;

	bow_dbgLog("compiling %s shader at \"%s\"",typStr,pth);

	FILE * fp = fopen(pth,"r");

	free(pth);

	if (fp == nullptr) {
		bow_logErr("unable to open shader source");
		return true;
	}

	fseek(fp,0x0,SEEK_END);
	zap_sz const filsz = (zap_sz)ftell(fp);
	rewind(fp);

	static_assert(sizeof (GLchar) == sizeof (char));
	GLchar * const src = malloc(filsz + 0x1u);

	if (src == nullptr) {
		bow_logErr("unable to allocate memory for shader source");
		return true;
	}

	fread(src,sizeof (GLchar),filsz,fp);
	fclose(fp);

	src[filsz] = '\x00';

	GLuint shdRef = glCreateShader(typ);
	glShaderSource(shdRef,0x1,(GLchar const * const *)&src,nullptr);

	free(src);

	glCompileShader(shdRef);

	GLint compStat;
	glGetShaderiv(shdRef,GL_COMPILE_STATUS,&compStat);
	unlikely (compStat == GL_FALSE) return true;

	*refPtr = shdRef;

	return false;
}
