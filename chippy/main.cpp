#include <iostream>

#include "./cpu.hpp"

bool use_program(chippy::memory_t&, std::string);
bool use_counter(chippy::memory_t&);

int main()
{
    chippy::cpu cpu;
    
    // if (!use_counter(cpu.memory))
    if (!use_program(cpu.memory, "roms/lunar-lander.ch8")) 
        std::cerr << "failed to load program\n";

    for (;;)
    {
        cpu.cycle();
        std::cin.get();
    }

    return 0;
}

bool use_counter(chippy::memory_t& memory)
{
    return memory.load_rom(
        std::vector<std::uint16_t>({
            0x6000, // V0 - which digit
            0x6301, // V3 - increment for digit (1)
            0x6100, // V1 - x-cor of sprite
            0x6200, // V2 - y-cor of sprite
            
            0xF029, // set addr reg to digit
            0x00e0, // clear screen
            0xD125, // draw digit at x, y cors

            0x8034, // V0 += V3 (digit += 1)
            0x4010, // if V0 != 16
            0x6000, // set V0 to 0
            0x1200 + 4*2, // jump 4 instructions from start
        }),
        true
    );
}

bool use_program(chippy::memory_t& memory, std::string fname)
{
    return memory.load_rom(fname);
}