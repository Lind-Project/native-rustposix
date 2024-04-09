# Compiler and linker settings
CC=gcc
CFLAGS=-c
LDFLAGS=-L. -lrustposix

# Default source files
SRC=lind_platform.c
OBJ=$(SRC:.c=.o)

# Pattern rule for object files
%.o: %.c
	@echo "Don't forget export LD_LIBRARY_PATH"
	$(CC) $(CFLAGS) $< -o $@

# Dynamic target for compiling programs with a main function
%: %.o $(OBJ)
	$(CC) $< $(OBJ) $(LDFLAGS) -o $@

# Clean the build
clean:
	rm -f *.o *~ core

