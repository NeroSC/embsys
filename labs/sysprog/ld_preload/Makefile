GCC = gcc
SONAME = libhook.so

all : hook

hook:
	$(GCC) -g -c -fPIC hook.c -o hook.o
	$(GCC) -g -shared -Wl,-soname,$(SONAME) -o $(SONAME) hook.o -lm
