#include <iostream>

#include "./chip8/ops/opcodes.hpp"
#include "./chip8/cpu.hpp"

int main()
{
    chippy::cpu cpu;
    
    // if (!cpu.memory.load_rom("./roms/tetris.rom"))
    // {
    //     std::cout << "Couldn't load rom :( \n";
    //     return 1;
    // }


    cpu.memory.load_rom(std::vector<std::uint16_t>({ 
        0xee00, 0xe000, 0x55f2
    }));

    cpu.dispatcher = chippy::kDispatcher;

    for (;;)
    {
        cpu.cycle();
    }

    // for (int i = 0; i < 3; ++i) 
    // {
    //     chippy::opcode opcode = cpu.get_opcode();

    //     std::cout << "READ: ";
    //     std::cout << std::hex;

    //     std::cout << opcode.get();

    //     std::cout << std::dec;
    //     std::cout << "\n";

    //     cpu.pc += 2;
    // }

    return 0;
}