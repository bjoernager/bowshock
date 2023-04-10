// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>

#include <cstdio>
#include <cstdlib>
#include <glad/glad.h>
#include <stdexcept>
#include <zap/mem.hh>
#include <zap/str.hh>

void ::bow::bow::compShd(GLuint & shd,char const * const nm,GLenum const typ) {
	char const * typStr;
	
	char const * typExt;
	::zap::sz    typExtLen;
	switch (typ) {
	default:
		bow_logErr("bad shader type %lX",static_cast<unsigned long>(typ));
		::bow::abrt();
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
	::zap::sz    dirLen;
	bow_setStrLen(dir,dirLen,bow_datDir "/shaders");

	::zap::sz const nmLen  = ::zap::strlen(nm);
	::zap::sz const pthLen = dirLen + 0x1u + nmLen + 0x1u + typExtLen + 0x1u + sizeof (::bow::shdFilExt);

	char * pth = new char[pthLen + 0x1u];

	pth = ::zap::cp(pth,dir,dirLen).dest;
	*pth++ = '/';
	pth = ::zap::cp(pth,nm,nmLen).dest;
	*pth++ = '.';
	pth = ::zap::cp(pth,typExt,typExtLen).dest;
	*pth++ = '.';
	pth = ::zap::cp(pth,::bow::shdFilExt,sizeof (::bow::shdFilExt)).dest;
	*pth   = '\x00';
	pth -= pthLen;

	bow_logDbg("compiling %s shader at \"%s\"",typStr,pth);

	FILE * fp = ::std::fopen(pth,"r");

	delete[] pth;

	if (fp == nullptr) {throw ::std::runtime_error {"unable to open shader source"};}

	::std::fseek(fp,0x0,SEEK_END);
	::zap::sz const filsz = static_cast<::zap::sz>(ftell(fp));
	::std::rewind(fp);

	static_assert(sizeof (GLchar) == sizeof (char));
	GLchar * const src = new GLchar[filsz + 0x1u];

	::std::fread(src,sizeof (GLchar),filsz,fp);
	::std::fclose(fp);

	src[filsz] = '\x00';

	shd = glCreateShader(typ);
	glShaderSource(shd,0x1,(GLchar const * const *)&src,nullptr);

	delete[] src;

	glCompileShader(shd);

	GLint compStat;
	glGetShaderiv(shd,GL_COMPILE_STATUS,&compStat);
	if (compStat == GL_FALSE) [[unlikely]] {throw ::std::runtime_error {"unable to compile shader"};}
}
