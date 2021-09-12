#ifndef __CPU_HPP__
#define __CPU_HPP__

#include <array>
#include <string>
#include <vector>

#include <iostream>
#include <fstream>

namespace chippy
{
    // Registers from V0-VF
    constexpr std::size_t kRegisters = 0x10;
    using registers_t = std::array<std::uint8_t, kRegisters>;

    // 16 16-bit value stack
    constexpr std::size_t kStackSize = 16;
    using stack_t = std::array<std::uint16_t, kStackSize>;

    // memory for 0x000-0xFFF (inclusive)
    constexpr std::size_t kBufferBytes = 0x1000;
    using memory_t = std::array<char, kBufferBytes>; //std::vector<char>;

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
        std::uint8_t sound; // sound timer (60hz)

        // ROM
        bool load_rom(const std::string &rompath)
        {
            std::ifstream file;
            file.open(rompath, std::ios::in);

            if (!file.is_open())
            {
                std::cerr << "Failed to open " << rompath << "\n";
                return false;
            }

            for (std::size_t i = 0x200;; ++i)
            {
                // get byte pairs & check for error
                char nextbyte[1];
                file.read(nextbyte, 1);

                // maybe do a size check to see if it was
                // a bad error instead of runnign out of stuff
                if (!file.good())
                    break;

                // store byte in memory
                mem[i] = nextbyte[0];
            }

            file.close();
            return true;
        }

        bool load_rom(const std::vector<char> &rombytes)
        {
            for (std::size_t i = 0; i < rombytes.size(); ++i)
                mem[i + 0x200] = rombytes[i];

            return true;
        }

        bool load_rom(const std::vector<std::uint16_t> &rombytes)
        {
            for (std::size_t i = 0; i < rombytes.size(); ++i)
            {
                auto opcode = rombytes[i];

                mem[(i * 2) + 0x201] = (opcode & 0xFF00) >> 8;
                mem[(i * 2) + 0x200] = (opcode & 0x00FF) >> 0;
            }

            return true;
        }
    
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