#include "./cpu.hpp"
#include <cstdlib> // random

using namespace chippy;

opcode cpu::get_opcode() const
{
    // the order of upper and lower bits is big-endian,
    // as specified by the chip-8 language 
    char upper = memory[pc + 0];
    char lower = memory[pc + 1];

    std::uint16_t data =
        (static_cast<unsigned char>(upper) << 8) +
        (static_cast<unsigned char>(lower) << 0);

    return opcode{data};
}

void cpu::cycle()
{
    opcode opcode = get_opcode();
    auto id = opcode.id();

    std::cout << opcode << " (" << id << ") \n";

    handle(opcode);
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
            pc += 2;
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

        pc += 2;
        break;
    }

    case 0x4:
    {
        if (v[op.x()] != op.byte())
            pc += 2;

        pc += 2;
        break;
    }

    case 0x5:
    {
        if (v[op.x()] == v[op.y()])
            pc += 2;

        pc += 2;
        break;
    }

    case 0x6:
    {
        v[op.x()] = op.byte();
        pc += 2;
        break;
    }

    case 0x7:
    {
        v[op.x()] += op.byte();
        pc += 2;
        break;
    }

    case 0x8:
    {
        // for conveience
        std::uint16_t x = op.x();
        std::uint16_t y = op.y();

        // lowest nibble is type of register operation
        auto type = op.extract(0);
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

        pc += 2;
        break;
    }

    case 0x9:
    {
        if (v[op.x()] != v[op.y()])
            pc += 2;

        pc += 2;
        break;
    }

    case 0xA:
    {
        address = op.addr();
        pc += 2;
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
        pc += 2;
        break;
    }

    case 0xD:
    {
        sprite sprite { op.x(), op.y(), {} };

        // std::cout << op.x() << ", " << op.y() << " \n";
        std::cout << address << " to " << (address + op.nibble()) << " | size (" << op.nibble() << ")\n";
        for (
            std::size_t readaddr = address, endaddr = address + op.nibble();
            readaddr < endaddr;
            ++readaddr
        ) {
            sprite.bytes.push_back(memory[readaddr]);
        }

        v[0xF] = display.frame.xoreq(sprite);
        std::cout << display.frame << "\n";
        pc+=2;
        break;
    }

    case 0xE:
    {
        break;
    }

    case 0xF:
    {
        break;
    }
    }
};
