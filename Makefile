CC=gcc

CCFLAGS=

OBJECTS:=$(wildcard *.c)
HEADERS:=$(wildcard *.h)
TARGETS:=$(patsubst %.c, %.o, $(OBJECTS))

.PHONY: all clean run


all: $(TARGETS)


$(TARGETS): %.o : %.c $(HEADERS)
	$(CC) $(CCFLAGS) $< -o $@
	
run: $(TARGETS)
	./$<

clean:
	rm -rf $(TARGETS)
