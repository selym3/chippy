#ifndef __GPU_HPP__
#define __GPU_HPP__

#include <SFML/Graphics.hpp>

namespace chippy
{

// construct simple frame buffer
constexpr std::size_t kPixelRows = 64;
constexpr std::size_t kPixelCols = 32;

struct frame
{

};

constexpr std::size_t kPixelWidth = 10;
constexpr std::size_t kPixelHeight = 10;

// constexpr std::size_t kScreenWidth = 

struct gpu
{
    sf::RenderWindow window;

    // gpu() :
    //     window { sf::VideoMode(640, "CHIP-8", }
    // {

    // }

};

}

#endif