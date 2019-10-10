NAME = open

UNAME := $(shell uname)

ifeq ($(UNAME),Linux)
LIB_NAME = lib$(NAME).so
CFLAGS += -Wl,--no-as-needed
else ifeq ($(UNAME),Darwin)
LIB_NAME = lib$(NAME).dylib
else
$(error Platform not supported)
endif

CFLAGS += -shared -fPIC -ldl

all: $(LIB_NAME)

$(LIB_NAME): $(CURDIR)/open.c
	$(CC) -o $@ $(CFLAGS) $^

clean:
	rm -rf $(LIB_NAME)

.PHONY: clean
