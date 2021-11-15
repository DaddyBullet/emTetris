#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <gui_generated/containers/BlockBase.hpp>
#include <touchgfx/Color.hpp>
#include <gui/common/Coord.hpp>

class Block : public BlockBase
{
public:
    Block();
    Block(const Block &blk);
    virtual ~Block() {}

    virtual void initialize();

    void setColor(touchgfx::colortype new_color);
    touchgfx::colortype getColor() const {return color;}

    void setCoords(int x, int y) {coord = {x, y};}
    Coord getCoords() const;

protected:

private:
    touchgfx::colortype color = {};
    Coord coord = {0, 0};
};

#endif // BLOCK_HPP
