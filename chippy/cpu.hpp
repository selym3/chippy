#ifndef __CPU_HPP__
#define __CPU_HPP__

#include <array>
#include <iostream>

#include "./ops/opcode.hpp"
#include "./hardware/memory.hpp"

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
        memory_t memory;

        // REGISTERS
        registers_t v;         // variables (0x0-0xF)
        std::uint16_t address; // address
        std::uint8_t pc;       // program counter

        // STACK
        std::uint8_t sp; // stack pointer
        stack_t stack;   // stack

        // TIMERS
        std::uint8_t delay; // delay timer (60 hz)
        std::uint8_t sound; // sound timer (60 hz)

        opcode get_opcode() const;
        void cycle();
        void handle_opcode(cpu &cpu, opcode op);
    };
}

#endif