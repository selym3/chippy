#ifndef __CPU_HPP__
#define __CPU_HPP__

#include <array>
#include <iostream>

#include "./ops/opcode.hpp"

#include "./hardware/memory.hpp"
#include "./hardware/stack.hpp"
#include "./hardware/gpu.hpp"
#include "./hardware/keyboard.hpp"

namespace chippy
{
    // Registers from V0-VF
    constexpr std::size_t kRegisters = 0x10;
    using registers_t = std::array<std::uint8_t, kRegisters>;

    // 16 16-bit value stack
    constexpr std::size_t kStackSize = 16;
    using stack_t = stack<kStackSize>;

    // 4096 byte memory
    constexpr std::size_t kBufferBytes = 0x1000;
    using memory_t = memory<kBufferBytes>;

    struct cpu
    {
        // MEMORY
        memory_t memory;

        // REGISTERS
        registers_t v;                 // variables (0x0-0xF)
        std::uint16_t address;         // address
        std::uint16_t pc = kFreeStart; // program counter

        // STACK
        stack_t stack; // stack

        // DISPLAY
        gpu display;

        // KEYBOARD
        keyboard keys;

        // TIMERS
        std::uint8_t delay; // delay timer (60 hz)
        std::uint8_t sound; // sound timer (60 hz)

        // read and execute a single opcode
        void cycle();
        opcode get_opcode() const;
        void handle(opcode op);

        // perform cycles and timer updates
        void run();
    };
}

#endif