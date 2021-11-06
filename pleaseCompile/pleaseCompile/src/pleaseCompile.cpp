#include "game.h"

int main()
{
    Game GameConsole;
    
    if (GameConsole.Construct(WINDOW_WIDTH, WINDOW_HEIGHT, PIXEL_SIZE, PIXEL_SIZE));
        GameConsole.Start();
}
