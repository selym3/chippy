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
        std::cout << op << "\n";
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
        std::cout << op << "\n";
        cpu.pc+=2;
    },

    // 0x4???
    [](cpu& cpu, const opcode& op) 
    {
        std::cout << op << "\n";
        cpu.pc+=2;
    },

    // 0x5???
    [](cpu& cpu, const opcode& op) 
    {
        std::cout << op << "\n";
        cpu.pc+=2;
    },

    // 0x6???
    [](cpu& cpu, const opcode& op) 
    {
        std::cout << op << "\n";
        cpu.pc+=2;
    },
    
    // 0x7???
    [](cpu& cpu, const opcode& op) 
    {
        std::cout << op << "\n";
        cpu.pc+=2;
    },

    // 0x8???
    [](cpu& cpu, const opcode& op) 
    {
        std::cout << op << "\n";
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