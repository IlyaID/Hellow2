SOURCES := $(wildcard *.c)
EXECUTABLES := $(SOURCES:.c=)

all: $(EXECUTABLES)

%: %.c
	gcc $< -o $@