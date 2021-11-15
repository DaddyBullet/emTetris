#ifndef FIELD_HPP
#define FIELD_HPP

#include <gui_generated/containers/FieldBase.hpp>
#include <touchgfx/widgets/canvas/Line.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <array>
#include <memory>

class Field : public FieldBase
{
public:
    Field();
    virtual ~Field() {}

    void move_left();
    void move_right();
    void move_down();
    int move_down_result();
    void rotate_piece();

    void step();
    int step_result();
    void new_game();

    bool check_out_of_field(Coord offset=Coord()) const;

    virtual void initialize();
protected:

private:
    static const int cols = 10;
    static const int rows = 21;

    typedef std::array<Block*, cols> row_t;
    typedef std::array<row_t, rows> table_t;

    static const int v_lines_count = cols + 1;
    static const int h_lines_count = rows + 1;

    touchgfx::PainterRGB565 line_painter = {};
    std::array<touchgfx::Line, v_lines_count> v_lines = {};
    std::array<touchgfx::Line, h_lines_count> h_lines = {};

    Coord getAbsTetrCoord(const Block &blk) const;

    table_t blk_table = {};

    bool check_collisions(Coord offset=Coord()) const;
    bool check_block_at(Coord coord) const;

    void transfer_block(const Block &block);

    int check_full_rows();


    /* Vector of steady blocks */

    /* Currently moving block */
};

#endif // FIELD_HPP
