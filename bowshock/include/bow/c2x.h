// Copyright 2022-2023 Gabriel Jensen.

#pragma once

#ifdef __GNUC__
#pragma GCC system_header
#elifdef _MSC_VER
#pragma system_header
#endif

#undef bool
#undef constexpr
#undef false
#undef nullptr
#undef reproducible
#undef static_assert
#undef thread_safe
#undef typeof
#undef true
#undef unreachable
#undef unsequenced

#define bool          _Bool
#define constexpr     static const
#define false         ((bool)+0x0u)
#define nullptr       ((void *)0x0u)
#define static_assert _Static_assert
#define thread_safe   _Thread_safe
#define typeof        __typeof__
#define true          ((bool)+0x1u)

#if defined(__GNUC__) || defined(__clang__)
#define unreachable ((void)__builtin_unreachable())
#elifdef __MSC_VER
#define unreachable ((void)__assume(false))
#else
#define unreachable ((void)0x0u)
#endif

#if __GNUC__
#define reproducible gnu::const
#define unsequenced  gnu::pure
#endif
