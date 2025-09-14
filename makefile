# Compiler and flags
CC = gcc
CFLAGS = -shared -fPIC -DKXVER=3 -I$(AF_PATH)/include
LDFLAGS = -L$(AF_PATH)/lib64 -lm -laf

# Source files
SRCS = fireq.c

# Output shared library
OUT = fireq.so

# Default target
all: $(OUT)

# Compile and link shared library
$(OUT): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $(OUT)

# Clean target to remove generated files
clean:
	rm -f $(OUT)

# Phony targets
.PHONY: all clean