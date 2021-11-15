#ifndef THETR_HPP
#define THETR_HPP

#include <gui_generated/containers/ThetrBase.hpp>
#include <gui/containers/Block.hpp>
#include <touchgfx/Color.hpp>
#include <array>
#include <gui/common/Coord.hpp>

class Thetr : public ThetrBase
{
public:
    Thetr();
    virtual ~Thetr() {}

    virtual void initialize();

    void setBlockCoords(Block& block, int x, int y);
    void setBlockCoords(Block& block, Coord xy) {setBlockCoords(block, xy.getX(), xy.getY());}
    
    void reinit();

    void rotate(int times = 1);

    const std::array<Block, 4>& getBlocks() const;

    Coord getCoords() const;

    void stepDown();
    void stepRight();
    void stepLeft();

protected:

private:
    enum figure_t
    {
        FIGURE_I,
        FIGURE_L,
        FIGURE_ML,
        FIGURE_S,
        FIGURE_MS,
        FIGURE_T,
        FIGURE_BOX,
        FIGURES_NUM
    };

    figure_t figure;
    int rot = 0;
    touchgfx::colortype color = {};

    std::array<Block, 4> blocks = {};

    Coord coords = {-2, 3};

    void rotate_once();
};

#endif // THETR_HPP
