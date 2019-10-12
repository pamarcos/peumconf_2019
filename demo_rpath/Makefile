APP_NAME = app

UNAME := $(shell uname)

ifeq ($(UNAME),Linux)
LIB_NAME = libfoo.so
else ifeq ($(UNAME),Darwin)
LIB_NAME = libfoo.dylib
endif

APP_CFLAGS = -L. -lfoo -Wl,-rpath,@executable_path/../lib -Wl,-rpath,@executable_path
LIB_CFLAGS = -shared -fPIC -install_name @rpath/$(LIB_NAME)

all: $(APP_NAME) $(LIB_NAME) fake_foo

$(APP_NAME): app.c $(LIB_NAME)
	$(CC) -o $@ $(APP_CFLAGS) $<

fake_foo: $(LIB_NAME)
	$(MAKE) -C fake_foo

dist:
	$(MAKE) -C fake_foo dist

undist:
	$(MAKE) -C fake_foo undist

$(LIB_NAME): foo.c
	$(CC) -o $@ $(LIB_CFLAGS) $^

clean:
	rm -rf $(APP_NAME) $(LIB_NAME)
	$(MAKE) -C fake_foo clean

.PHONY: clean fake_foo dist undist
