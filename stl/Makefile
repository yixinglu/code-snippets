.PHONY: clean alloc pmr

alloc: allocator.cpp
	g++ -std=c++17 $< -o alloc.out

pmr: pmr.cpp
	g++ -std=c++17 $< -o pmr.out

clean:
	rm -rf *.out
