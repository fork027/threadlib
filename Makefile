CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar
ARFLAGS = rcs

# Target library
lib := libuthread.a

all: $(lib)

# Object files
context.o: context.c private.h
	$(CC) $(CFLAGS) -c $<

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c $<

uthread.o: uthread.c uthread.h private.h
	$(CC) $(CFLAGS) -c $<

# Static library archive
$(lib): context.o queue.o uthread.o
	$(AR) $(ARFLAGS) $@ $^

# Clean target
clean:
	rm -f $(lib) context.o queue.o uthread.o

.PHONY: all clean
