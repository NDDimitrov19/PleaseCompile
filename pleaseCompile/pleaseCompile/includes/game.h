#pragma once
#include <vector>
#include "maze.h"
#include "olcConsoleGameEngine.h"

class Game : public olcConsoleGameEngine
{
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

    void DrawRectangle(int x1, int y1, int x2, int y2, short c);

    void MovePlayer(float fElapsedTime);

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

