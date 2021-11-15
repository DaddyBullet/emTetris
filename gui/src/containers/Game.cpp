#include <gui/containers/Game.hpp>

Game::Game()
{

}

void Game::initialize()
{
    GameBase::initialize();
}


void Game::tick()
{
    if (state == GAME_STATE_RUN)
    {
        int result = field1.step_result();
        if (result == -1)
        {
            state = GAME_STATE_OVER;
            game_over.setVisible(true);
            game_over.invalidate();
        }
        else
        {
            score += result;
            Unicode::snprintf(lines_lbBuffer, LINES_LB_SIZE, "%d", (int32_t)score);
            lines_lb.setWildcard(lines_lbBuffer);
            lines_lb.invalidate();
        }
    }

}

void Game::new_game()
{
    field1.new_game();
    game_over.setVisible(false);
    game_over.invalidate();
    pause_lb.setVisible(false);
    pause_lb.invalidate();
    score = 0;
    Unicode::snprintf(lines_lbBuffer, LINES_LB_SIZE, "%d", (int32_t)score);
    lines_lb.setWildcard(lines_lbBuffer);
    lines_lb.invalidate();
    state = GAME_STATE_RUN;
}

void Game::toggle_pause()
{
    if (state == GAME_STATE_RUN)
    {
        state = GAME_STATE_PAUSE;
        pause_lb.setVisible(true);
        pause_lb.invalidate();
    }
    else if (state == GAME_STATE_PAUSE)
    {
        state = GAME_STATE_RUN;
        pause_lb.setVisible(false);
        pause_lb.invalidate();
    }
}