all:
	clang++ -std=c++17 -Wall -c chippy/cpu.cpp -o bin/cpu
	clang++ -std=c++17 -lsfml-window -lsfml-system -lsfml-graphics chippy/main.cpp bin/* -o bin/main
	./bin/main