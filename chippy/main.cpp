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

    cpu.memory.load_rom(
        std::vector<std::uint16_t>({
            0xA000 + 0x0200 + 0x000A, // set address register to 3 ahead from start of program memory
            0x2000 + 0x0200 + 0x0004, // call subroutine starting at 0x204
            0x00e0, // clear display 
            0xD008, // draw command
            0x00ee, // return to draw subroutine

            // sprite data (8 bytes)
            0b1111111110000001,
            0b1000000111111111
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