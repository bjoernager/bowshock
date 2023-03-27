LD = $(CC)

CFLAGS := \
	-Iinclude  \
	-Wall      \
	-Wextra    \
	-Wpedantic \
	-Wno-attributes \
	-Wno-gnu-folding-constant \
	-Wno-gnu-empty-initializer \
	-Wno-gnu-zero-variadic-macro-arguments \
	-g         \
	-pipe      \
	-std=gnu2x

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

LDLIBS := \
	-lGL   \
	-lflux \
	-lglfw \
	-lm    \
	-lwebp \
	-lzap

OBJS := \
	source/bs/gendat.o      \
	source/bs/init.o        \
	source/bs/initdat.o     \
	source/bs/loop.o        \
	source/bs/quit.o        \
	source/gfx/initgfx.o    \
	source/info/objtypstr.o \
	source/info/shipmass.o  \
	source/lgc/addobj.o     \
	source/lgc/freeobjs.o   \
	source/lgc/grav.o       \
	source/lgc/mv.o         \
	source/sav/cont.o       \
	source/sav/sav.o

BIN := bowshock.elf

HDRS := \
	include/bow/bs.h   \
	include/bow/info.h \
	include/bow/lgc.h  \
	include/bow/sav.h

.PHONY: clean purge

$(BIN): $(OBJS)
	$(LD) -o$(@) $(^) $(LDLIBS)

$(OBJS): $(HDRS)

clean:
	$(RM) $(OBJS)

purge: clean
	$(RM) $(BIN)
