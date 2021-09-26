all:
	clang++ -std=c++20 -Wall -c src/cpu.cpp -o bin/cpu
	clang++ -std=c++20 -Wall -lsfml-window -lsfml-system -lsfml-graphics src/main.cpp bin/* -o bin/main
	./bin/main