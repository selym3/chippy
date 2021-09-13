all:
	clang++ -c chippy/cpu.cpp -o bin/cpu
	clang++ chippy/main.cpp bin/* -o bin/main
	./bin/main