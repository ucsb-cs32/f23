TARGETS = echo1 echo2 echo3 echo4
.PHONY: all clean

CC     = gcc
CFLAGS = -Wall -Wextra -g

NO_ASLR    = -fno-pie -no-pie
NO_CANARY  = -fno-stack-protector
NO_RELRO   = -Wl,-z,norelro
# Partial RELRO: -Wl,-z,relro,-z,lazy
NO_NXSTACK = -z execstack

all: $(TARGETS)

echo1: echo1.c
	$(CC) $(CFLAGS) $(NO_ASLR) $(NO_CANARY) $(NO_RELRO) $(NO_NXSTACK) -o $@ $<

echo2: echo2.c
	$(CC) $(CFLAGS) $(NO_ASLR) $(NO_RELRO) $(NO_NXSTACK) -o $@ $<

echo3: echo3.c
	$(CC) $(CFLAGS) $(NO_RELRO) $(NO_NXSTACK) -o $@ $<

echo4: echo4.c
	$(CC) $(CFLAGS) $(NO_RELRO) $(NO_NXSTACK) -o $@ $<

echo5: echo5.c
	$(CC) $(CFLAGS) $(NO_RELRO) -o $@ $<


clean:
	rm -f $(TARGETS)
