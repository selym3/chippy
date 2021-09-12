#ifndef __CPU_HPP__
#define __CPU_HPP__

#include <array>
#include <string>
#include <vector>

#include <iostream>
#include <fstream>

#include "./memory.hpp"

namespace chippy
{
    // Registers from V0-VF
    constexpr std::size_t kRegisters = 0x10;
    using registers_t = std::array<std::uint8_t, kRegisters>;

    // 16 16-bit value stack
    constexpr std::size_t kStackSize = 16;
    using stack_t = std::array<std::uint16_t, kStackSize>;

    // 4k memory
    constexpr std::size_t kBufferBytes = 0x1000;
    using memory_t = memory<kBufferBytes>;

    struct cpu
    {
        // MEMORY
        memory_t mem;

        // REGISTERS
        registers_t v; // variables (0x0-0xF)
        std::uint16_t address; // address
        std::uint8_t pc; // program counter

        // STACK
        std::uint8_t sp; // stack pointer
        stack_t stack; // stack

        // TIMERS
        std::uint8_t delay; // delay timer (60 hz)
        std::uint8_t sound; // sound timer (60 hz)

        // OPCODES
        std::uint16_t get_opcode() const
        {
            char upper = mem[0x200 + pc+0];
            char lower = mem[0x200 + pc+1];

            return (static_cast<unsigned char>(upper)<<8) +
                   (static_cast<unsigned char>(lower)<<0);
        }

    };
}

#endif