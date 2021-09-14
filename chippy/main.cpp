#include <iostream>

#include "./cpu.hpp"

int main()
{
    chippy::cpu cpu;
    
    // if (!cpu.memory.load_rom("./roms/tetris.rom"))
    // {
    //     std::cout << "Couldn't load rom :( \n";
    //     return 1;
    // }

    cpu.memory.load_rom(std::vector<std::uint16_t>({
        0x0af0
    }));

    for (;;)
    {
        cpu.cycle();
    }

    return 0;
}