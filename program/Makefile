CC := gcc
CFLAGS := -std=c99 -Wall  -I ./include/ -lm -fPIE
LDFLAGS := -pthread -L ./lib
LDLIBS := -lm -lSDL2 -ldl

HEADERS := $(wildcard *.h)
SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))

.PHONY: all clean

$(OBJECTS): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

program: $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:
	-rm -f *.o
	-rm -f program
