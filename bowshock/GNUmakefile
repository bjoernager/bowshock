# Copyright 2022-2023 Gabriel Jensen.

LD = $(CC)

CFLAGS := \
	-Iinclude            \
	-Wall                \
	-Wextra              \
	-Wmissing-prototypes \
	-Wpedantic           \
	-Wno-attributes      \
	-g                   \
	-pipe                \
	-std=gnu2x

ifeq "$(CC)" "clang"
CFLAGS := \
	$(CFLAGS)                              \
	-Wno-gnu-folding-constant              \
	-Wno-gnu-empty-initializer             \
	-Wno-gnu-zero-variadic-macro-arguments 
endif

ifeq "$(c2xcompat)" "true"
CFLAGS := \
	$(CFLAGS)                                 \
	-D"bool=_Bool"                            \
	-D"false=((_Bool)+0x0u)"                  \
	-D"nullptr=((void *)0x0u)"                \
	-D"static_assert=_Static_assert"          \
	-D"thread_safe=_Thread_safe"              \
	-D"typeof=__typeof__"                     \
	-D"true=((_Bool)+0x1u)"                   \
	-D"unreachable()=__builtin_unreachable()"
endif

ifeq "$(debug)" "true"
CFLAGS := \
	$(CFLAGS)        \
	-D"bow_dbg=true" \
	-Og
else
CFLAGS := \
	$(CFLAGS)             \
	-D"_FORTIFY_SOURCE=2" \
	-DNDEBUG              \
	-Ofast
endif

OBJS := \
	source/bs/abrt.o       \
	source/bs/chkparams.o  \
	source/bs/getquot.o    \
	source/bs/getsavpth.o  \
	source/bs/help.o       \
	source/bs/init.o       \
	source/bs/initrnd.o    \
	source/bs/initsig.o    \
	source/bs/intro.o      \
	source/bs/loop.o       \
	source/bs/quit.o       \
	source/bs/rnd.o        \
	source/gfx/drw.o       \
	source/gfx/initgfx.o   \
	source/lgc/addobj.o    \
	source/lgc/freeobjs.o  \
	source/lgc/gensys.o    \
	source/lgc/grav.o      \
	source/lgc/mv.o        \
	source/lgc/objtypstr.o \
	source/lgc/shipmass.o  \
	source/lgc/sim.o       \
	source/sav/gendat.o    \
	source/sav/cont.o      \
	source/sav/rstart.o    \
	source/sav/sav.o

LDLIBS := \
	-lGL   \
	-lflux \
	-lglfw \
	-lm    \
	-lzap

BIN := bowshock.elf

HDRS := \
	include/bow/bs.h  \
	include/bow/gfx.h \
	include/bow/lgc.h \
	include/bow/sav.h

.PHONY: clean purge

$(BIN): $(OBJS)
	$(LD) -o$(@) $(^) $(LDLIBS)

$(OBJS): $(HDRS)

clean:
	$(RM) $(OBJS)

purge: clean
	$(RM) $(BIN)
