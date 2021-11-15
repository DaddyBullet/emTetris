#include <gui/containers/Thetr.hpp>
#include <gui/containers/Block.hpp>

#include <stdlib.h>
#include <time.h>

Thetr::Thetr()
{
    srand(time(nullptr));

    reinit();

    for (Block& b: blocks)
    {
        add(b);
    }
}

void Thetr::initialize()
{
    ThetrBase::initialize();
}


void Thetr::rotate(int times)
{
    times %= 4;

    for (int i = 0; i < times; i++)
    {
        rotate_once();
    }
    invalidate();
}

void Thetr::setBlockCoords(Block& block, int x, int y)
{
    block.setCoords(x, y);
    block.setXY(1 + 33 * x, 1 + 33 * y);
}

void Thetr::reinit()
{
    figure = static_cast<figure_t>(rand() % FIGURES_NUM);
    rot = rand() % 4;
    color = touchgfx::Color::getColorFrom24BitRGB(rand() % 200, rand() % 200, rand() % 200);

    coords = Coord(3, -2);

    switch (figure)
    {
    case FIGURE_I:
        setBlockCoords(blocks[0], 1, 0);
        setBlockCoords(blocks[1], 1, 1);
        setBlockCoords(blocks[2], 1, 2);
        setBlockCoords(blocks[3], 1, 3);
        break;
    
    case FIGURE_L:
        setBlockCoords(blocks[0], 1, 0);
        setBlockCoords(blocks[1], 1, 1);
        setBlockCoords(blocks[2], 1, 2);
        setBlockCoords(blocks[3], 2, 2);
        break;
    
    case FIGURE_ML:
        setBlockCoords(blocks[0], 2, 0);
        setBlockCoords(blocks[1], 2, 1);
        setBlockCoords(blocks[2], 2, 2);
        setBlockCoords(blocks[3], 1, 2);
        break;
        
    case FIGURE_S:
        setBlockCoords(blocks[0], 0, 2);
        setBlockCoords(blocks[1], 1, 2);
        setBlockCoords(blocks[2], 1, 1);
        setBlockCoords(blocks[3], 2, 1);
        break;
    
    case FIGURE_MS:
        setBlockCoords(blocks[0], 0, 1);
        setBlockCoords(blocks[1], 1, 1);
        setBlockCoords(blocks[2], 1, 2);
        setBlockCoords(blocks[3], 2, 2);
        break;

    case FIGURE_T:
        setBlockCoords(blocks[0], 0, 1);
        setBlockCoords(blocks[1], 1, 1);
        setBlockCoords(blocks[2], 1, 2);
        setBlockCoords(blocks[3], 2, 1);
        break;
    
    case FIGURE_BOX:
        setBlockCoords(blocks[0], 1, 1);
        setBlockCoords(blocks[1], 1, 2);
        setBlockCoords(blocks[2], 2, 1);
        setBlockCoords(blocks[3], 2, 2);
        break;
    
    default:
        break;
    }

    rotate(rot);

    for (Block& b: blocks)
    {
        b.setColor(color);
    }

    invalidate();
}

void Thetr::rotate_once()
{
    for (Block& b : blocks)
    {
        setBlockCoords(b, 3 - b.getCoords().getY(), b.getCoords().getX());    
    }
}

const std::array<Block, 4>& Thetr::getBlocks() const
{
    return blocks;
}

Coord Thetr::getCoords() const
{
    return coords;
}

void Thetr::stepDown()
{
    coords = coords + Coord(0, 1);
}
void Thetr::stepRight()
{
    coords = coords + Coord(1, 0);
}
void Thetr::stepLeft()
{
    coords = coords + Coord(-1, 0);
}