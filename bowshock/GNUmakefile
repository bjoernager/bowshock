LD := $(CC)

CFLAGS := \
	-Iinclude  \
	-Ofast     \
	-Wall      \
	-Wextra    \
	-Wpedantic \
	-Wno-gnu-empty-initializer \
	-Wno-gnu-zero-variadic-macro-arguments \
	-g         \
	-std=c2x

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
	source/lgc/mv.o

BIN := bowshock.elf

HDRS := \
	include/bow/bs.h   \
	include/bow/info.h \
	include/bow/lgc.h  \
	include/bow/sav.h

$(BIN): $(OBJS)
	$(LD) -o$(@) $(^) $(LDLIBS)

$(OBJS): $(HDRS)
