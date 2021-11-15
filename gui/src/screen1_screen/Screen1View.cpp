#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::handleTickEvent()
{
    if(waitCounter > 0)
    {
        waitCounter--;
        if(waitCounter == 0)
        {
            game1.tick_act();

            waitCounter = waitCounterTimeout;
        }
    }
}
