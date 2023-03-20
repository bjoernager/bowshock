LD := $(CC)

CFLAGS := \
	-Iinclude  \
	-Ofast     \
	-Wall      \
	-Wextra    \
	-Wpedantic \
	-Wno-gnu-folding-constant \
	-Wno-gnu-empty-initializer \
	-Wno-gnu-zero-variadic-macro-arguments \
	-g         \
	-pipe      \
	-std=c2x

ifeq "$(c2xcompat)" "true"
CFLAGS := \
	$(CFLAGS)                        \
	-Dbool="_Bool"                   \
	-Dfalse="((_Bool)0x0u)"          \
	-Dnullptr="((void *)0x0u)"       \
	-Dstatic_assert="_Static_assert" \
	-Dthread_safe="_Thread_safe"     \
	-Dtypeof="__typeof__"            \
	-Dtrue="((_Bool)0x1u)"
endif

ifeq "$(debug)" "true"
CFLAGS := \
	$(CFLAGS) \
	-Dbow_dbg=true
endif

LDLIBS := \
	-lGL   \
	-lflux \
	-lglfw \
	-lm    \
	-lzap

OBJS := \
	source/bs/gendat.o     \
	source/bs/init.o       \
	source/bs/initdat.o    \
	source/bs/loop.o       \
	source/bs/quit.o       \
	source/gfx/initgfx.o   \
	source/info/shipmass.o \
	source/lgc/grav.o      \
	source/lgc/mv.o        \
	source/sav/cont.o      \
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
