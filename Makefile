P := main
OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))
CC := gcc
CFLAGS := -I$(HOME)/local/include -fms-extensions -Wall -Wextra
LDFLAGS := -L$(HOME)/local/lib
LDLIBS := -lm


ifeq ($(BUILD_PROFILE), release)
	CFLAGS := $(CFLAGS) -O3 -Werror
else
	CFLAGS := $(CFLAGS) -g -Og -DDEBUG_ASSERTIONS=1
endif


ifeq ($(ENABLE_GPROF), 1)
	CFLAGS := $(CFLAGS) -pg
	LDFLAGS := $(LDFLAGS) -pg
endif


$(P): $(OBJECTS)

clean:
	rm -rf $(P) *.o
