all: mc.out remc.out

CC=g++
CPPFLAGS=-O3 -march=native

mc.out: saizeriya_mc.cpp mc.hpp remc.hpp
	$(CC) $(CPPFLAGS) $< -o $@

remc.out: saizeriya_mc.cpp mc.hpp remc.hpp
	$(CC) $(CPPFLAGS) -DRE $< -o $@

clean:
	rm -f mc.out remc.out
