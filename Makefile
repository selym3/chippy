all:
	clang++ -std=c++20 -Wall -c chippy/cpu.cpp -o bin/cpu
	clang++ -std=c++20 -Wall -lsfml-window -lsfml-system -lsfml-graphics chippy/main.cpp bin/* -o bin/main
	./bin/main