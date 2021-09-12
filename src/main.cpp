#include <iostream>
#include <fstream>

#include <array>
#include <algorithm>
#include <string>


#include "./hardware/cpu.hpp"

int main()
{
    chippy::cpu cpu;
    if (!cpu.load_rom("./roms/tetris.rom"))
    {
        std::cout << "Couldn't load rom :( \n";
        return 1;
    }

    for (int i = 0; i < 5; ++i) 
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