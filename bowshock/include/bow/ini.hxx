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
		::GLuint       shdprg;
	};

	struct trmopt {
		char const * savpth;
		bool         hassavpth:0x1u;
		bool         newsav:0x1u;
		bool         skp:0x1u;
	};

	class bow {
	public:
		[[noreturn]] auto ini(int argc,char const * const * argv) noexcept -> void;

	private:
		::bow::plydat plydat;
		::bow::gfxdat gfxdat;

		auto getsavpth()                                                  noexcept -> char const *;
		auto getquo(   char const * * quo,char const * * src,::zp::i8 id) noexcept -> void;

		auto priquo() noexcept -> void;

		[[noreturn]] auto pricrd()                    noexcept -> void;
		[[noreturn]] auto hlp(char const * prognm) noexcept -> void;

		auto chkpar(trmopt & opt,int argc,char const * const * argv) noexcept -> void;

		auto compshdprg(::GLuint & shdprg,char const * nam)             noexcept -> void;

		auto inigfx() noexcept -> void;
		auto inirnd() noexcept -> void;
		auto inisig() noexcept -> void;

		auto polevt() noexcept -> bool;

		auto srtseq() noexcept -> bool;
		auto lop()    noexcept -> void;

		[[noreturn]] auto exi(::bow::cnd stat) noexcept -> void;
	};

	extern ::std::sig_atomic_t volatile gotint;
}
