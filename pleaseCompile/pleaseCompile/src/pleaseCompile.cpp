#include <iostream>
#include <vector>
#include <set>
#include "maze.h"
#include "olcConsoleGameEngine.h"

class Game : public olcConsoleGameEngine
{
private:

public:
    Game() {}
    float PlayerX = 0;
    float PlayerY = 0;
    float PlayerSpeed = 30;
    struct coords
    {
        int x;
        int y;
    };

    std::vector< std::pair<coords, coords> > wallCoords;

    void DrawRectangle(int x1, int y1, int x2, int y2, short c) {
        DrawLine(x1, y1, x1, y2, PIXEL_SOLID, c);
        DrawLine(x1, y2, x2, y2, PIXEL_SOLID, c);
        DrawLine(x2, y2, x2, y1, PIXEL_SOLID, c);
        DrawLine(x2, y1, x1, y1, PIXEL_SOLID, c);
    }
    void MovePlayer(float fElapsedTime) {
        short movementX = 0;
        short movementY = 0;
        if (m_keys[L'W'].bHeld || m_keys[VK_UP].bHeld)
            movementY = -1;
        if (m_keys[L'D'].bHeld || m_keys[VK_RIGHT].bHeld)
            movementX = 1;
        if (m_keys[L'S'].bHeld || m_keys[VK_DOWN].bHeld)
            movementY = 1;
        if (m_keys[L'A'].bHeld || m_keys[VK_LEFT].bHeld)
            movementX = -1;
        if ((movementX == 1 && movementY == 1) || (movementX == -1 && movementY == -1) || (movementX == 1 && movementY == -1) || (movementX == -1 && movementY == 1))
        {
            PlayerX += movementX * PlayerSpeed * fElapsedTime / 2;
            PlayerY += movementY * PlayerSpeed * fElapsedTime / 2;
        }
        else
        {
            PlayerX += movementX * PlayerSpeed * fElapsedTime;
            PlayerY += movementY * PlayerSpeed * fElapsedTime;
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

     Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_GREEN);

     DrawRectangle(PlayerX, PlayerY, PlayerX + 10, PlayerY + 10, FG_BLACK);

     for (auto wall : this->wallCoords)
     {
         DrawLine(wall.first.x, wall.first.y, wall.second.x, wall.second.y, FG_BLACK);
     }

     MovePlayer(fElapsedTime);
        return 1;
    }

};
int main()
{
  Game GameConsole;

    GameConsole.ConstructConsole(200,200,4, 4);
    GameConsole.Start();
}
