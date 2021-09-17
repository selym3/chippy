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

    // cpu.memory.load_rom(
    //     std::vector<std::uint16_t>({
    //         0xA000 + 0x0200 + 0x0009, // set address register to start of sprite data
    //         0x2000 + 0x0200 + 0x0004, // call subroutine starting at 0x204
    //         0x00e0, // clear display 
    //         0xD004, // draw command
    //         0x00ee, // return to draw subroutine

    //         // sprite data (4 bytes)
    //         0b0000000100000010,
    //         0b0000001100000100,
    //     }),
    //     true
    // );

    cpu.memory.load_rom(
        std::vector<std::uint16_t>({
            0xA000 + 0x0200 + 0x0006,
            0xD634,
            0x1000 + 0x0200 + 0x0002,
            0b0000000100000010,
            0b0000001100000100,
        }),
        true
    );

    for (;;)
    {
        cpu.cycle();
        std::cin.get();
    }

    return 0;
}