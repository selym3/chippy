#ifndef __OPCODES_HPP__
#define __OPCODES_HPP__

#include <array>
#include <functional>

#include "./opcode.hpp"
#include "./optypes.hpp"
#include "../cpu.hpp"

#include <iostream>

namespace chippy
{

const std::array<OpHandler, 16> kDispatcher 
{
    // 0x0???
    [](cpu& cpu, const opcode& op) 
    {
        switch (op.get())
        {
            case 0x00E0:
            {
                break;
            }

            case 0x00EE:
            {

                break;
            }
            
            default:
            {
                std::cout << "ignored\n";
                break;
            }
        }
        cpu.pc+=2;
    },

    // 0x1???
    [](cpu& cpu, const opcode& op) 
    {
        std::cout << op << "\n";
        cpu.pc+=2;
    },

    // 0x2???
    [](cpu& cpu, const opcode& op) 
    {
        std::cout << op << "\n";
        cpu.pc+=2;
    },

    // 0x3???
    [](cpu& cpu, const opcode& op) 
    {
        if (cpu.v[op.x()] == op.byte())
        {
            cpu.pc+=2;
        }
        cpu.pc+=2;
    },

    // 0x4???
    [](cpu& cpu, const opcode& op) 
    {
        if (cpu.v[op.x()] != op.byte())
        {
            cpu.pc+=2;
        }
        cpu.pc+=2;
    },

    // 0x5???
    [](cpu& cpu, const opcode& op) 
    {
        if (cpu.v[op.x()] == cpu.v[op.y()])
        {
            cpu.pc+=2;
        }
        cpu.pc+=2;
    },

    // 0x6???
    [](cpu& cpu, const opcode& op) 
    {
        cpu.v[op.x()] = op.byte();
        cpu.pc+=2;
    },
    
    // 0x7???
    [](cpu& cpu, const opcode& op) 
    {
        cpu.v[op.x()] += op.byte();
        cpu.pc+=2;
    },

    // 0x8???
    [](cpu& cpu, const opcode& op) 
    {
        std::uint8_t x = op.x();
        std::uint8_t y = op.y();

        // lowest nibble is type of math
        auto type = op.extract(0); 
        switch (type)
        {
            case 0x0: 
            { 
                cpu.v[x] = cpu.v[y];
                break; 
            }

            case 0x1:
            { 
                cpu.v[x] |= cpu.v[y];
                break; 
            }

            case 0x2:
            { 
                cpu.v[x] &= cpu.v[y];
                break;
            }

            case 0x3:
            { 
                cpu.v[x] ^= cpu.v[y];
                break; 
            }

            case 0x4:
            { 
                std::uint16_t add = cpu.v[x] + cpu.v[y];
                cpu.v[0xF] = add > 255;
                cpu.v[x] = static_cast<std::uint8_t>(add&0x00FF);
                break; 
            }

            case 0x5:
            {
                cpu.v[0xF] = cpu.v[x] > cpu.v[y];
                cpu.v[x] -= cpu.v[y];
                break;
            }

            case 0x6:
            {
                cpu.v[0xF] = cpu.v[x]&1;
                cpu.v[x] >>= 1;
                break;
            }

            case 0x7:
            {
                cpu.v[0xF] = cpu.v[y] > cpu.v[x];
                cpu.v[x] = cpu.v[y] - cpu.v[x];
                break;
            }

            case 0xE:
            {
                auto msb = 0b10000000;
                cpu.v[0xF] = ((cpu.v[x]&msb)>>7);
                cpu.v[x] <<= 1;
                break;
            }
            
            default: 
            {
                std::cout << "ignored\n";
                break;
            }
        }
        cpu.pc+=2;
    },

    // 0x9???
    [](cpu& cpu, const opcode& op) 
    {
        std::cout << op << "\n";
        cpu.pc+=2;
    },

    // 0xA???
    [](cpu& cpu, const opcode& op) 
    {
        std::cout << op << "\n";
        cpu.pc+=2;
    },

    // 0xB???
    [](cpu& cpu, const opcode& op) 
    {
        std::cout << op << "\n";
        cpu.pc+=2;
    },

    // 0xC???
    [](cpu& cpu, const opcode& op) 
    {
        std::cout << op << "\n";
        cpu.pc+=2;
    },

    // 0xD???
    [](cpu& cpu, const opcode& op) 
    {
        std::cout << op << "\n";
        cpu.pc+=2;
    },

    // 0xE???
    [](cpu& cpu, const opcode& op) 
    {
        std::cout << op << "\n";
        cpu.pc+=2;
    },

    // 0xF???
    [](cpu& cpu, const opcode& op) 
    {
        std::cout << op << "\n";
    },
  
};

}

#endif