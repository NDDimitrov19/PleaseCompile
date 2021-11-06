#include "game.h"

int main()
{
    Game GameWindow;
    
    if (GameWindow.Construct(WINDOW_WIDTH, WINDOW_HEIGHT, PIXEL_SIZE, PIXEL_SIZE));
        GameWindow.Start();
}
