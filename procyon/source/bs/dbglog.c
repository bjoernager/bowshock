#include <acm/bs.h>

#include <stdarg.h>
#include <stdio.h>

void acm_dbglog(char const * const _fmt,...) {
	va_list args;
	va_start(args,_fmt);
	vfprintf(stderr,_fmt,args);
	va_end(args);
}
