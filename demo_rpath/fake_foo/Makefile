NAME = foo

UNAME := $(shell uname)

ifeq ($(UNAME),Linux)
LIB_NAME = lib$(NAME).so
else ifeq ($(UNAME),Darwin)
LIB_NAME = lib$(NAME).dylib
endif

ORIG_FOO = $(CURDIR)/../libfoo.dylib
LIB_CFLAGS = -shared -fPIC -Wl,-reexport_library,$(ORIG_FOO) -Wl,-rpath,@executable_name -install_name @rpath/$(LIB_NAME)
DIST_DIR = $(CURDIR)/../../lib

all: $(LIB_NAME)

$ORIG_FOO:

$(LIB_NAME): fake_foo.c $ORIG_FOO
	$(CC) -o $@ $(LIB_CFLAGS) $<
	install_name_tool $@ -change @rpath/libfoo.dylib $(ORIG_FOO)

dist: $(LIB_NAME)
	mkdir -p $(DIST_DIR)
	cp -f $(LIB_NAME) $(DIST_DIR)

undist:
	rm -rf $(DIST_DIR)

clean:
	rm -rf $(LIB_NAME) $(DIST_DIR)

.PHONY: clean dist undist
