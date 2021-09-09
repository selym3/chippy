#include <iostream>
#include <fstream>

#include <array>
#include <algorithm>
#include <string>

char itohc(std::uint8_t a) 
{
    if (a < 10)
        return a+'0';
    else
        return (a-10)+'A';
} 

std::string hex(std::uintmax_t a) 
{
    std::string hex;

    do {
        hex += itohc(a%16);
        a/=16;
    } while (a>=1);

    std::reverse(hex.begin(), hex.end());
    return hex;
}


int main()
{
    // Create file stream
    auto filename = "./roms/tetris.rom";
    std::ifstream file(
        filename,
        std::ios::binary | std::ios::in
    );

    if (!file.is_open())
    {
        std::cerr << "Failed to open " << filename;
        return 1;
    }

    // Read file stream
    using Chunk = std::uint16_t;
    using Byte = std::uint8_t;

    for (;;)
    {
        // Read next chunk
        // Chunk chunk = 0;
        // file.read(reinterpret_cast<char*>(chunk), 2);

        char buffer[2];
        file.read(buffer, 2);

        Chunk chunk = (static_cast<Byte>(buffer[0]) << 8) +
                      (static_cast<Byte>(buffer[1]) << 0);

        // Print chunk as nibbles
        std::cout << "READ: ";

        std::cout << hex((chunk & 0xF000) >> 12) << " ";
        std::cout << hex((chunk & 0x0F00) >>  8) << " ";
        std::cout << hex((chunk & 0x00F0) >>  4) << " ";
        std::cout << hex((chunk & 0x000F) >>  0) << " ";

        std::cout << "\n";

        // Check error bits for stopping point
        if (!file.good())
            break;
    }

    file.close();

    return 0;
}