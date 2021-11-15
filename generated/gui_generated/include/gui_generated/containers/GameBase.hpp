/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef GAMEBASE_HPP
#define GAMEBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <gui/containers/Field.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/ButtonWithIcon.hpp>

class GameBase : public touchgfx::Container
{
public:
    GameBase();
    virtual ~GameBase() {}
    virtual void initialize();

    /*
     * Custom Actions
     */
    virtual void new_game_act();
    virtual void move_right_act();
    virtual void move_left_act();
    virtual void move_down_act();
    virtual void rotate_act();
    virtual void toggle_pause_act();
    virtual void tick_act();

    /*
     * Virtual Action Handlers
     */
    virtual void new_game()
    {
        // Override and implement this function in Game
    }

    virtual void toggle_pause()
    {
        // Override and implement this function in Game
    }

    virtual void move_down()
    {
        // Override and implement this function in Game
    }

    virtual void move_left()
    {
        // Override and implement this function in Game
    }

    virtual void move_right()
    {
        // Override and implement this function in Game
    }

    virtual void rotate()
    {
        // Override and implement this function in Game
    }

    virtual void tick()
    {
        // Override and implement this function in Game
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box bg;
    Field field1;
    touchgfx::TextArea main_lb;
    touchgfx::ButtonWithLabel new_game_bt;
    touchgfx::ButtonWithLabel pause;
    touchgfx::TextAreaWithOneWildcard lines_lb;
    touchgfx::TextArea pause_lb;
    touchgfx::ButtonWithIcon up_bt;
    touchgfx::ButtonWithIcon right_bt;
    touchgfx::ButtonWithIcon down_bt;
    touchgfx::ButtonWithIcon left_bt;
    touchgfx::TextArea game_over;

    /*
     * Wildcard Buffers
     */
    static const uint16_t LINES_LB_SIZE = 64;
    touchgfx::Unicode::UnicodeChar lines_lbBuffer[LINES_LB_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<GameBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // GAMEBASE_HPP