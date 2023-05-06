// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>

#include <cstdlib>
#include <ly/io>
#include <ly/fs>
#include <glad/glad.h>
#include <stdexcept>
#include <zp/mem>
#include <zp/str>

void ::bow::bow::compShd(GLuint & shd,char const * const nm,GLenum const typ) {
	char const * typStr;
	
	char const * typExt;
	::zp::siz    typExtLen;
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
	::zp::siz    dirLen;
	bow_setStrLen(dir,dirLen,bow_datDir "/shaders");

	::zp::siz const nmLen  = ::zp::strlen(nm);
	::zp::siz const pthLen = dirLen + 0x1u + nmLen + 0x1u + typExtLen + 0x1u + sizeof (::bow::shdFilExt);

	char * pth = new char[pthLen + 0x1u];

	pth = ::zp::cpy(pth,dir,dirLen).dst;
	*pth++ = '/';
	pth = ::zp::cpy(pth,nm,nmLen).dst;
	*pth++ = '.';
	pth = ::zp::cpy(pth,typExt,typExtLen).dst;
	*pth++ = '.';
	pth = ::zp::cpy(pth,::bow::shdFilExt,sizeof (::bow::shdFilExt)).dst;
	*pth   = '\x00';
	pth -= pthLen;

	bow_logDbg("compiling %s shader at \"%s\"",typStr,pth);

	::ly::fil fil;
	::ly::err err = fil.opn(pth,::ly::mod::red,::ly::kep);

	if (err != ::ly::err::ok) [[unlikely]] {throw ::std::runtime_error {"unable to open shader source"};}

	::zp::siz const filsiz = [&pth]() {
		::ly::pthinf pthinf;
		::ly::sttpth(pthinf,pth);

		return pthinf.siz;
	}();

	delete[] pth;

	static_assert(sizeof (GLchar) == sizeof (char));
	GLchar * const src = new GLchar[filsiz + 0x1u];

	err = fil.red(src,filsiz);
	if (err != ::ly::err::ok) {throw ::std::runtime_error {"unable to read shader source"};}
	fil.cls();

	src[filsiz] = '\x00';

	shd = glCreateShader(typ);
	glShaderSource(shd,0x1,(GLchar const * const *)&src,nullptr);

	delete[] src;

	glCompileShader(shd);

	GLint compStat;
	glGetShaderiv(shd,GL_COMPILE_STATUS,&compStat);
	if (compStat == GL_FALSE) [[unlikely]] {throw ::std::runtime_error {"unable to compile shader"};}
}
