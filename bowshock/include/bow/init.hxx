// Copyright 2022-2023 Gabriel Jensen.

#pragma once

#include <bow/run.hxx>

#include <GLFW/glfw3.h>
#include <csignal>
#include <glad/glad.h>

namespace bow {
	constexpr char const shdFilExt[] = "glsl";

	struct gfxDat {
		::GLFWwindow * win;
		GLuint       shdProg;
	};

	struct termOpts {
		char const * savPth;
		bool         hasSavPth:0x1u;
		bool         newSav:0x1u;
		bool         skip:0x1u;
	};

	class bow {
	public:
		             bow( int argc,char const * const * argv) noexcept;
		[[noreturn]] ~bow()                                   noexcept;

	private:
		::bow::plDat  plDat;
		::bow::gfxDat gfxDat;

		char const * getSavPth()                                                    noexcept;
		void         getQuot(  char const * * quot,char const * * src,::zp::i8m id) noexcept;

		void priQuot() noexcept;

		[[noreturn]] void cred()                    noexcept;
		[[noreturn]] void help(char const * progNm) noexcept;

		void chkParams(termOpts & opts,int argc,char const * const * argv) noexcept;

		void compShd(    GLuint & shd,    char const * nm,GLenum typ);
		void compShdProg(GLuint & shdProg,char const * nm)            noexcept;

		void initGfx() noexcept;
		void initRnd() noexcept;
		void initSig() noexcept;

		void init(int argc,char const * const * argv) noexcept;

		bool pollEvts() noexcept;

		bool intro() noexcept;
		void loop()  noexcept;

		[[noreturn]] void quit(::bow::stat stat) noexcept;
	};

	extern ::std::sig_atomic_t volatile gotIntr;
}
