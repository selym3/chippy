#include <iostream>

#include "./hardware/cpu.hpp"
#include "./opcode.hpp"

int main()
{
    chippy::cpu cpu;

    if (!cpu.mem.load_rom("./roms/tetris.rom"))
    {
        std::cout << "Couldn't load rom :( \n";
        return 1;
    }

    // cpu.load_rom(std::vector<std::uint16_t>({ 
    //     0xee00, 0xe000, 0x55f2
    // }));

    for (int i = 0; i < 3; ++i) 
    {
        chippy::opcode opcode{cpu.get_opcode()};

        std::cout << "READ: ";
        std::cout << std::hex;

        std::cout << (opcode.extract(3));
        std::cout << (opcode.extract(2));
        std::cout << (opcode.extract(1));
        std::cout << (opcode.extract(0));

        std::cout << std::dec;
        std::cout << "\n";

        cpu.pc += 2;
    }

    return 0;
}