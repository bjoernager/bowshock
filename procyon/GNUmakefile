# TOOLS

# TOOL FLAGS

CFLAGS := \
	-D_POSIX_C_SOURCE=200809L \
	-Iinclude \
	-O3 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-g \
	-march=native \
	-std=c2x

ifeq "$(debug)" "true"
CFLAGS := \
	$(CFLAGS) \
	-Dacm_dbg
endif

LDLIBS := \
	-lGL \
	-lflux \
	-lglfw \
	-lzap

# HEADERS

HDRS := \
	include/acm/bs.h

# BINARIES

OBJS := \
	source/bs/cont.o \
	source/bs/dbglog.o \
	source/bs/exit.o \
	source/bs/init.o \
	source/bs/sav.o \
	source/bs/shipnm.o \
	source/gfx/initgfx.o \
	source/main.o

BIN := procyon.elf

# TARGETS

.PHONY: clean purge

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o$(@) $(^) $(LDLIBS)

$(OBJS): $(HDRS)

clean:
	$(RM) $(OBJS)

purge: clean
	$(RM) $(LIB)
