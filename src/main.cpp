#include <iostream>

#include "./hardware/cpu.hpp"

int main()
{
    chippy::cpu cpu;

    if (!cpu.load_rom("./roms/tetris.rom"))
    {
        std::cout << "Couldn't load rom :( \n";
        return 1;
    }

    // NOTE: the instructions are big-endian, so 0xe000 -> 0x00e0
    // cpu.load_rom(std::vector<std::uint16_t>({ 
    //     0xee00, 0xe000, 0x55f2
    // }));

    for (int i = 0; i < 3; ++i) 
    {
        auto opcode = cpu.get_opcode();

        std::cout << "READ: ";
        std::cout << std::hex;

        std::cout << ((opcode&0xF000)>>12);
        std::cout << ((opcode&0x0F00)>> 8);
        std::cout << ((opcode&0x00F0)>> 4);
        std::cout << ((opcode&0x000F)>> 0);

        std::cout << std::dec;
        std::cout << "\n";

        cpu.pc += 2;
    }

    return 0;
}