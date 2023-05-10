// Copyright 2022-2023 Gabriel Jensen.

#pragma once

#include <bow/run.hxx>

#include <GLFW/glfw3.h>
#include <csignal>
#include <glad/glad.h>

namespace bow {
	constexpr char const shdfilext[] = "glsl";

	struct gfxdat {
		::GLFWwindow * win;
		::GLuint       shdprog;
	};

	struct trmopt {
		char const * savPth;
		bool         hassavpth:0x1u;
		bool         newsav:0x1u;
		bool         skip:0x1u;
	};

	class bow {
	public:
		[[noreturn]] auto ini(int argc,char const * const * argv) noexcept -> void;

	private:
		::bow::pldat  pldat;
		::bow::gfxdat gfxdat;

		auto getsavpth()                                                    noexcept -> char const *;
		auto getquo(   char const * * quo,char const * * src,::zp::i8 id) noexcept -> void;

		auto priquo() noexcept -> void;

		[[noreturn]] auto crd()                    noexcept -> void;
		[[noreturn]] auto hlp(char const * progNm) noexcept -> void;

		auto chkpar(trmopt & opt,int argc,char const * const * argv) noexcept -> void;

		auto cmpshd(     ::GLuint & shd,    char const * nam,GLenum typ)          -> void;
		auto compshdprog(::GLuint & shdprog,char const * nam)            noexcept -> void;

		auto inigfx() noexcept -> void;
		auto inirnd() noexcept -> void;
		auto inisig() noexcept -> void;

		auto polevt() noexcept -> bool;

		auto srtseq() noexcept -> bool;
		auto lop()   noexcept -> void;

		[[noreturn]] auto exi(::bow::cnd stat) noexcept -> void;
	};

	extern ::std::sig_atomic_t volatile gotint;
}
