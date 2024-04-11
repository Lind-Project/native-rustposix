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

# Build user tests
test:
	@echo "Building user tests"
	CC="$(CC)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" ./build.sh tests.txt

# Build user performance tests
perf-test:
	@echo "Building user performance tests"
	CC="$(CC)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" ./build.sh perf_tests.txt

# Clean the build
clean:
	find tests/ -type f ! -name "*.*" -delete
	rm -f -- **/*.o *.so *~ core
