CC = gcc
CFLAGS = -shared -fPIC -DKXVER=3 -I$(AF_PATH)/include
LDFLAGS = -L$(AF_PATH)/lib64 -lm -laf
SRCS = fireq.c
OUT = fireq.so

all: $(OUT)

$(OUT): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $(OUT)
	
clean:
	rm -f $(OUT)

.PHONY: all clean
