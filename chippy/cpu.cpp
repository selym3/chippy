#include "./cpu.hpp"
#include <cstdlib> // random

using namespace chippy;

opcode cpu::get_opcode() const
{
    // the order of upper and lower bits is big-endian,
    // as specified by the chip-8 language 
    std::uint8_t upper = memory[pc + 0];
    std::uint8_t lower = memory[pc + 1];

    std::uint16_t data =
        (static_cast<std::uint16_t>(upper) << 8) +
        (static_cast<std::uint16_t>(lower) << 0);

    return opcode{data};
}

void cpu::cycle()
{

    // read & increment
    opcode opcode = get_opcode();
    pc+=2;

    std::cout << opcode << "\n";

    // execute opcode
    handle(opcode);

    // TODO: handle timers, etc.
    display.draw();
}

void cpu::handle(opcode op)
{
    switch (op.id())
    {

    case 0x0:
    {
        switch (op.get())
        {
        case 0x00E0:
        {
            display.clear();
            break;
        }

        case 0x00EE:
        {
            std::cout << "popping from stack\n";
            std::cout << "updating pc from " << pc;
            pc = stack.pop();
            std::cout << " to " << pc << "\n";
            break;
        }

        default:
        {
            std::cout << "ignored\n";
            break;
        }
        }

        break;
    }

    case 0x1:
    {
        pc = op.addr();
        break;
    }

    case 0x2:
    {
        std::cout << "pushing to stack\n";
        stack.push(pc);

        pc = op.addr();
        std::cout << "updating program counter (" << (stack.top) << ")" << " to " << pc << "\n";
        break;
    }

    case 0x3:
    {
        if (v[op.x()] == op.byte())
            pc += 2;

        break;
    }

    case 0x4:
    {
        if (v[op.x()] != op.byte())
            pc += 2;

        break;
    }

    case 0x5:
    {
        if (v[op.x()] == v[op.y()])
            pc += 2;

        break;
    }

    case 0x6:
    {
        v[op.x()] = op.byte();
        break;
    }

    case 0x7:
    {
        v[op.x()] += op.byte();
        break;
    }

    case 0x8:
    {
        // for conveience
        std::uint16_t x = op.x();
        std::uint16_t y = op.y();

        // lowest nibble is type of register operation
        auto type = op.nibble();
        switch (type)
        {
        case 0x0:
        {
            v[x] = v[y];
            break;
        }

        case 0x1:
        {
            v[x] |= v[y];
            break;
        }

        case 0x2:
        {
            v[x] &= v[y];
            break;
        }

        case 0x3:
        {
            v[x] ^= v[y];
            break;
        }

        case 0x4:
        {
            std::uint16_t add = v[x] + v[y];
            v[0xF] = add > 255;

            // NOTE: this might not work
            v[x] = static_cast<std::uint8_t>(add & 0x00FF);
            break;
        }

        case 0x5:
        {
            v[0xF] = v[x] > v[y];
            v[x] -= v[y];
            break;
        }

        case 0x6:
        {
            v[0xF] = v[x] & 1;
            v[x] >>= 1;
            break;
        }

        case 0x7:
        {
            v[0xF] = v[y] > v[x];
            v[x] = v[y] - v[x];
            break;
        }

        case 0xE:
        {
            auto msb = 0b10000000;
            v[0xF] = ((v[x] & msb) >> 7);
            v[x] <<= 1;
            break;
        }

        default:
        {
            std::cout << "ignored\n";
            break;
        }
        }

        break;
    }

    case 0x9:
    {
        if (v[op.x()] != v[op.y()])
            pc += 2;

        break;
    }

    case 0xA:
    {
        address = op.addr();
        break;
    }

    case 0xB:
    {
        pc = v[0x0] + op.addr();
        break;
    }

    case 0xC:
    {
        auto random = std::rand() % 256;
        v[op.x()] = random & op.byte();
        break;
    }

    case 0xD:
    {
        // prepare sprite to draw
        sprite sprite { v[op.x()], v[op.y()], {} };

        // read from the address register to rows of sprite
        // std::cout << op.x() << ", " << op.y() << " \n";
        std::cout << address << " to " << (address + op.nibble()) << " | size (" << op.nibble() << ")\n";
        for (
            std::uint16_t readaddr = address, endaddr = address + op.nibble();
            readaddr < endaddr;
            ++readaddr
        ) {
            sprite.bytes.push_back(memory[readaddr]);
        }

        // xor and collision
        auto collision = display.frame.xoreq(sprite);
        v[0xF] = collision;

        std::cout << "Collision status: " << collision << "\n";

        break;
    }

    case 0xE:
    {
        const auto which = op.byte();
        const auto key = v[op.x()];

        switch (which)
        {
        case 0x9E:
        {
            if (keys.pressed(key))
                pc+=2;
            break;
        }

        case 0xA1:
        {
            if (!keys.pressed(key))
                pc+=2;
            break;
        }
        }
    }

    case 0xF:
    {
        // lowest 2 bits are type of operation
        const auto type = op.byte();
        const auto x = op.x();

        switch (type)
        {
            case 0x07:
            {
                v[x] = delay;
                break;
            }
            case 0x0A:
            {
                for (;;) 
                {
                    // optional uint8_t
                    auto keyPressed = keys.any();

                    if (keyPressed.has_value()) {
                        v[x] = keyPressed.value();
                        break; 
                    }
                }
                break;
            }
            case 0x15:
            {
                delay = v[x];
                break;
            }
            case 0x18:
            {
                sound = v[x];
                break;
            }
            case 0x1E:
            {
                address += v[x];
                break;
            }
            case 0x29:
            {
                address = kFontStart +  // where the font data starts
                    5 *                 // bytes per digit
                    v[x];               // which digit to draw

                break;
            }
            case 0x33:
            {
                memory[address + 0] = (v[x]/100);   // hundreds digit
                memory[address + 1] = (v[x]/10)%10; // tens digit
                memory[address + 2] = (v[x])%10;    // ones digit

                break;
            }
            case 0x55:
            {
                std::uint16_t regaddr = address;
                for (std::uint16_t i = 0; i < x; ++i)
                    memory[regaddr++] = v[i];
                
                break;
            }
            case 0x65:
            {
                for (std::uint16_t i = 0; i < x; ++i) 
                    v[i] = memory[address + i];
                
                break;
            }
            default: 
            {
                std::cout << "Ignored\n";
                break;
            }
        }

        break;
    }
    }
};
