#include <iostream>
#include <vector>
#include "maze.h"
#include "olcPixelGameEngine.h"

#define WINDOW_WIDTH 200
#define WINDOW_HEIGHT 200
#define PIXEL_SIZE 4

class Game : public olc::PixelGameEngine
{
public:
    Game() {}
private:
    struct Player {
        float x;
        float y;
        float speed;
    };

    
    struct coords
    {
        int x;
        int y;
    };
    std::vector< std::pair<coords, coords> > wallCoords;

    void MovePlayer(float fElapsedTime);
    int mazeSize[2] = { 10 , 10 };
    Maze maze = Maze(mazeSize[0], mazeSize[1]);
    int mazeWallSize = WINDOW_HEIGHT / mazeSize[1];
    Player player = { (float)(mazeWallSize / 4),(float)(mazeWallSize / 4),30.0f };
    bool OnUserCreate() override;

    bool OnUserUpdate(float fElapsedTime) override;

};