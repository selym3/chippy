#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

#include <array>
#include <vector>
#include <string>

#include <fstream>
#include <iostream>

namespace chippy
{

// struct memrange
// {
//     const std::size_t start, end;
//     const std::size_t size;
//     constexpr memrange(std::size_t s, std::size_t e) :
//         start{s}, end{e}, size{e-s+1}
//     {
//     }
// };

constexpr std::size_t kFontStart = 0x000;
constexpr std::size_t kFontEnd = 0x1FF;

constexpr std::size_t kFreeStart = 0x200;
constexpr std::size_t kFreeEnd = 0xEFF;
constexpr std::size_t kFreeSize = kFreeEnd - kFreeStart + 1;

constexpr std::size_t kDisplayStart = 0xF00;
constexpr std::size_t kDisplayEnd = 0xFFF;

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

        std::size_t i;
        for (i = kFreeStart; i <= kFreeEnd; ++i)
        {
            // get byte pairs & check for error
            char nextbyte[1];
            file.read(nextbyte, 1);

            // this means the parsing finished before free memory ended
            if (!file.good())
                break;

            // store byte in memory
            buffer[i] = nextbyte[0];
        }

        file.close();

        if (i > kFreeEnd) 
        {
            std::cerr << "Failed to fully load " << rompath << ", too big for free memory of " << kFreeSize << " bytes.\n";
            return false;
        }
        return true;
    }

    bool load_rom(const std::vector<char>& rombytes)
    {
        if (rombytes.size() > kFreeSize) 
        {
            std::cerr << "Cannot load rombytes of " << (rombytes.size()*2) << " bytes into free memory of " << kFreeSize << " bytes.\n";
            return false;
        }

        for (std::size_t i = 0; i < rombytes.size(); ++i)
            buffer[i + 0x200] = rombytes[i];

        return true;
    }

    bool load_rom(const std::vector<std::uint16_t>& romcodes)
    {
        auto rombytes = romcodes.size() * 2;
        if (rombytes > kFreeSize) 
        {
            std::cerr << "Cannot load romcodes of " << (romcodes.size()*2) << " bytes into free memory of " << kFreeSize << " bytes.\n";
            return false;
        }

        for (std::size_t i = 0; i < romcodes.size(); ++i)
        {
            auto opcode = romcodes[i];

            buffer[(i * 2) + 0x200] = (opcode & 0x00FF) >> 0;
            buffer[(i * 2) + 0x201] = (opcode & 0xFF00) >> 8;
        }

        return true;
    }
};
/////

}

#endif