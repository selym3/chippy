all:
	clang++ -c chippy/cpu.cpp -o bin/cpu
	clang++ -lsfml-window -lsfml-system -lsfml-graphics chippy/main.cpp bin/* -o bin/main
	./bin/main