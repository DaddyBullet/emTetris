#ifndef GAME_HPP
#define GAME_HPP

#include <gui_generated/containers/GameBase.hpp>

class Game : public GameBase
{
public:
    Game();
    virtual ~Game() {}

    void new_game();
    void toggle_pause();

    void tick();

    virtual void move_down()
    {
        if (state == GAME_STATE_RUN){field1.move_down_act();  tick();}
    }

    virtual void move_left()
    {
        if (state == GAME_STATE_RUN){field1.move_left_act();}
    }

    virtual void move_right()
    {
        if (state == GAME_STATE_RUN){field1.move_right_act();}
    }

    virtual void rotate()
    {
        if (state == GAME_STATE_RUN){field1.rotate_act();}
    }

    virtual void initialize();
protected:

private:
    enum game_state_t
    {
        GAME_STATE_START,
        GAME_STATE_RUN,
        GAME_STATE_PAUSE,
        GAME_STATE_OVER,
    };

    game_state_t state = GAME_STATE_START;

    int score = 0;
};

#endif // GAME_HPP
