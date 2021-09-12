#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

#include <array>
#include <vector>
#include <string>

#include <fstream>
#include <iostream>

namespace chippy
{

// Wrapper around a buffer of memory
template <std::size_t Bytes>
struct memory
{
    using buffer_t = std::array<char, Bytes>;
    buffer_t buffer;
    memory() {}

    /***********************
     * READ & WRITE MEMORY *
     ***********************/

    const char& operator[](std::size_t index) const
    {
        return buffer[index];
    }

    char& operator[](std::size_t index)
    {
        return buffer[index];
    }

    /*************
     * WRITE ROM *
     *************/

    bool load_rom(const std::string& rompath)
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
            buffer[i] = nextbyte[0];
        }

        file.close();
        return true;
    }

    bool load_rom(const std::vector<char>& rombytes)
    {
        for (std::size_t i = 0; i < rombytes.size(); ++i)
            buffer[i + 0x200] = rombytes[i];

        return true;
    }

    bool load_rom(const std::vector<std::uint16_t>& rombytes)
    {
        for (std::size_t i = 0; i < rombytes.size(); ++i)
        {
            auto opcode = rombytes[i];

            buffer[(i * 2) + 0x200] = (opcode & 0x00FF) >> 0;
            buffer[(i * 2) + 0x201] = (opcode & 0xFF00) >> 8;
        }

        return true;
    }
};
/////

}

#endif