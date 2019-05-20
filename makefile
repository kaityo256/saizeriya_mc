all: a.out

CC=g++
CPPFLAGS=-O3 -march=native

a.out: saizeriya_mc.cpp mc.hpp
	$(CC) $(CPPFLAGS) $< -o $@

clean:
	rm -f a.out
