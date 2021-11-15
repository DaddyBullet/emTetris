#include <gui/containers/Block.hpp>

Block::Block()
{

}

Block::Block(const Block &blk)
{
    setColor(blk.getColor());
}

void Block::initialize()
{
    BlockBase::initialize();
}

void Block::setColor(touchgfx::colortype new_color)
{
    color = new_color;
    boxWithBorder1.setColor(color);
}

Coord Block::getCoords() const
{
    return coord;
}