#include <iostream>
#include <vector>
#include <set>
#include "maze.h"
#include "olcPixelGameEngine.h"

#define WINDOW_WIDTH = 200
#define WINDOW_HEIGHT = 200

class Game : public olc::PixelGameEngine
{
private:
    struct Player {
        float x;
        float y;
        float speed;
    };

public:
    Game() {}
    Player player = {0,0,30};
    struct coords
    {
        int x;
        int y;
    };

    std::vector< std::pair<coords, coords> > wallCoords;

    void MovePlayer(float fElapsedTime) {
        short movementX = 0;
        short movementY = 0;
        if (GetKey(olc::Key::W).bHeld || GetKey(olc::Key::UP).bHeld)
            movementY = -1;
        if (GetKey(olc::Key::D).bHeld || GetKey(olc::Key::RIGHT).bHeld)
            movementX = 1;
        if (GetKey(olc::Key::S).bHeld || GetKey(olc::Key::DOWN).bHeld)
            movementY = 1;
        if (GetKey(olc::Key::A).bHeld || GetKey(olc::Key::LEFT).bHeld)
            movementX = -1;
        if ((movementX == 1 && movementY == 1) || (movementX == -1 && movementY == -1) || (movementX == 1 && movementY == -1) || (movementX == -1 && movementY == 1))
        {
            player.x += movementX * player.speed * fElapsedTime / 2;
            player.y += movementY * player.speed * fElapsedTime / 2;
        }
        else
        {
            player.x += movementX * player.speed * fElapsedTime;
            player.y += movementY * player.speed * fElapsedTime;
        }
    }
    Maze maze;
    virtual bool OnUserCreate() {
        for (auto cell : maze.grid)
        {
            if (cell->walls[Maze::CellWallDirs::top]) {
                this->wallCoords.push_back({ {cell->x * 20, cell->y * 20}, {cell->x * 20 + 20, cell->y * 20} });
            }
            if (cell->walls[Maze::CellWallDirs::right]) {
                this->wallCoords.push_back({ {cell->x * 20 + 20, cell->y * 20}, {cell->x * 20 + 20, cell->y * 20 + 20} });
            }
            // Optimization
            //if (cell->walls[Maze::CellWallDirs::bottom]) {
            //    this->wallCoords.push_back({ {cell->x * 20, cell->y * 20 + 20}, {cell->x * 20 + 20, cell->y * 20 + 20} });
            //}
            //if (cell->walls[Maze::CellWallDirs::left]) {
            //    this->wallCoords.push_back({ {cell->x * 20, cell->y * 20}, {cell->x * 20, cell->y * 20 + 20} });
            //}
        }

        return 1;
    }
    
    virtual bool OnUserUpdate(float fElapsedTime) {

     FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::GREEN);
     DrawRect(player.x, player.y, 10, 10, olc::BLACK);
     // DrawCircle(player.x, player.y, 5, olc::BLACK);

     for (auto wall : this->wallCoords)
     {
         DrawLine(wall.first.x, wall.first.y, wall.second.x, wall.second.y, olc::BLACK);
     }

     MovePlayer(fElapsedTime);
        return 1;
    }

};
int main()
{
    Game GameConsole;
    if (GameConsole.Construct(200,200,4, 4))
        GameConsole.Start();
}
