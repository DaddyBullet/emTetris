#include <gui/containers/Field.hpp>
#include <touchgfx/Color.hpp>

Field::Field()
{
    line_painter.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    for (int i = 0; i < v_lines_count; i++)
    {
        v_lines[i].setPosition(i * 33, 0, 1, this->getHeight());
        v_lines[i].setStart(0, 0);
        v_lines[i].setEnd(0, (int)this->getHeight());
        v_lines[i].setLineWidth(1);
        v_lines[i].setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
        v_lines[i].setPainter(line_painter);
        add(v_lines[i]);
    }

    for (int i = 0; i < h_lines_count; i++)
    {
        h_lines[i].setPosition(0, i * 33, this->getWidth(), 1);
        h_lines[i].setStart(0, 0);
        h_lines[i].setEnd((int)this->getWidth(), 0);
        h_lines[i].setLineWidth(1);
        h_lines[i].setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
        h_lines[i].setPainter(line_painter);
        add(h_lines[i]);
    }
}

void Field::initialize()
{
    FieldBase::initialize();
}

void Field::step()
{
    step_result();
}

int Field::step_result()
{
    if (!check_collisions(Coord(0, 1)))
    {
        /* Copy blocks to table */
        for (const Block& b : piece.getBlocks())
        {
            transfer_block(b);
        }

        /* Check full lines */
        int result = check_full_rows();

        /* Generate new thetr */
        piece.reinit();
        piece.setXY(99, -66);

        if (!check_collisions())
        {
            /* Game_over */
            return -1;
        }
        piece.invalidate();
        return result;
    }
    else
    {
        piece.stepDown();
        piece.setY(piece.getY() + 33);

        invalidate();   
        return 0;
    }
}

void Field::move_left()
{
    if (check_out_of_field({-1, 0}) && check_collisions({-1, 0}))
    {
        piece.stepLeft();
        piece.setX(piece.getX() - 33);
        invalidate();
    }
}

void Field::move_right()
{
    if (check_out_of_field({1, 0}) && check_collisions({1, 0}))
    {
        piece.stepRight();
        piece.setX(piece.getX() + 33);
        invalidate();
    }
}

void Field::move_down()
{
    do
    {
        step();
    } while (check_collisions(Coord(0, 1)) == true);
}

void Field::rotate_piece()
{
    piece.rotate();
    if (!check_out_of_field())
    {
        if (piece.getCoords().getX() < 5)
        {
            move_right();
        }
        else
        {
            move_left();
        }
    }

    while (!check_collisions())
    {
        piece.rotate();
    }
    invalidate();

}

bool Field::check_out_of_field(Coord offset) const
{
    for (const Block& b : piece.getBlocks())
    {
        Coord tmp = getAbsTetrCoord(b) + offset;
        if (tmp.getX() < 0 || tmp.getX() >= cols)
        {
            return false;
        }
    }
    return true;
}

Coord Field::getAbsTetrCoord(const Block &blk) const
{
    return piece.getCoords() + blk.getCoords();
}

bool Field::check_collisions(Coord offset) const
{
    for (const auto &b : piece.getBlocks())
    {
        if ((getAbsTetrCoord(b) + offset).getY() >= rows)
        {
            return false;
        }

        if (check_block_at(getAbsTetrCoord(b) + offset))
        {
            return false;
        }
    }

    return true;
}

bool Field::check_block_at(Coord coord) const
{
    if (coord.getX() >= 0 && coord.getY() >= 0)
    {
        return blk_table[coord.getY()][coord.getX()] != nullptr;
    }
    return false;
}


void Field::transfer_block(const Block &block)
{
    int x = getAbsTetrCoord(block).getX();
    int y = getAbsTetrCoord(block).getY();
    if (x >= 0 && y >= 0)
    {
        if (blk_table[y][x])
        {
            remove(*blk_table[y][x]);
            delete blk_table[y][x];
            blk_table[y][x] = nullptr;
        }
        blk_table[y][x] = new Block(block);

        blk_table[y][x]->setXY(piece.getX() + block.getX(), piece.getY() + block.getY());

        add(*blk_table[y][x]);
    }
}

int Field::check_full_rows()
{
    int rows_deleted = 0;

    for (int row = rows - 1; row >= 0; row--)
    {
        bool has_empty = false;
        for (int col = 0; col < cols; col++)
        {
            if (!check_block_at(Coord(col, row + rows_deleted)))
            {
                has_empty = true;
                break;
            }
        }

        if (has_empty == false)
        {
            /* Remove blocks from row */
            for (int col = 0; col < cols; col++)
            {
                remove(*blk_table[row + rows_deleted][col]);
                delete blk_table[row + rows_deleted][col];
                blk_table[row + rows_deleted][col] = nullptr;
            }

            /* Move everithing down*/
            for (int r = row + rows_deleted - 1; r >= 0; r--)
            {
                for (int col = 0; col < cols; col++)
                {
                    blk_table[r + 1][col] = blk_table[r][col];
                    if (blk_table[r + 1][col] != nullptr)
                    {
                        blk_table[r + 1][col]->setY(blk_table[r + 1][col]->getY() + 33);
                        blk_table[r + 1][col]->invalidate();
                    }
                }
            }
            rows_deleted++;
        }
    }

    invalidate();
    return rows_deleted;
}

void Field::new_game()
{
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            if (blk_table[row][col] != nullptr)
            {
                remove(*blk_table[row][col]);
                delete blk_table[row][col];
                blk_table[row][col] = nullptr;
            }
        }
    }

    piece.reinit();
    piece.setXY(99, -66);

    invalidate();
}