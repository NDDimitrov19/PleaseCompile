#include <iostream>
#include <vector>
#include "maze.h"
#include "olcConsoleGameEngine.h"

class Game : public olcConsoleGameEngine
{
public:
    Game() {}
        

    void DrawRectangle(int x1, int y1, int x2, int y2, short c) {
        DrawLine(x1, y1, x1, y2, PIXEL_SOLID, c);
        DrawLine(x1, y2, x2, y2, PIXEL_SOLID, c);
        DrawLine(x2, y2, x2, y1, PIXEL_SOLID, c);
        DrawLine(x2, y1, x1, y1, PIXEL_SOLID, c);
    }

   /* void MakeBordersData() {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                if (map[j][k]) {

                    borders.push_back({ k,j });
                }
            }
        }
    }
    void MakeBorders() {
        for (auto iv : borders)
            DrawRectangle(iv.x1 * 20, iv.y1 * 20, iv.x1 * 20 + 20, iv.y1 * 20 + 20, FG_BLACK);
    }
    void Collision(float* dx, float* dy, float* orgDx, float* orgDy) {
        for (auto iv : borders) {

            if ((int)*dx / 20 == iv.x1 && (int)*dy / 20 == iv.y1) {
                if ((int)*dx / 20 == iv.x1) {
                    *dx = *orgDx;
                }
                if ((int)*dy / 20 == iv.y1) {
                    *dy = *orgDy;
                }

            }

            else if ((int)(*dx + 10) / 20 == iv.x1 && (int)(*dy + 10) / 20 == iv.y1)
            {
                if ((int)(*dx + 10) / 20 == iv.x1) {
                    *dx = *orgDx;
                }
                if ((int)(*dy + 10) / 20 == iv.y1) {
                    *dy = *orgDy;
                }

            }
            else if ((int)(*dx) / 20 == iv.x1 && (int)(*dy + 10) / 20 == iv.y1)
            {
                if ((int)(*dx) / 20 == iv.x1) {
                    *dx = *orgDx;
                }
                if ((int)(*dy + 10) / 20 == iv.y1) {
                    *dy = *orgDy;
                }

            }
            else if ((int)(*dx + 10) / 20 == iv.x1 && (int)(*dy) / 20 == iv.y1)
            {
                if ((int)(*dx + 10) / 20 == iv.x1) {
                    *dx = *orgDx;
                }
                if ((int)(*dy) / 20 == iv.y1) {
                    *dy = *orgDy;
                }

            }

        }
    }

    */
    Maze maze;
    virtual bool OnUserCreate() {

     //   MakeBordersData();

        return 1;
    }
    float dx = 0, dy = 0;
    float i = 60;
    virtual bool OnUserUpdate(float fElapsedTime) {

        Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_GREEN);

        float orgDx = dx;
        float orgDy = dy;
        if (m_keys[L'W'].bHeld)
            dy -= i * fElapsedTime;
        if (m_keys[L'A'].bHeld)
            dx -= i * fElapsedTime;
        if (m_keys[L'S'].bHeld)
            dy += i * fElapsedTime;
        if (m_keys[L'D'].bHeld)
            dx += i * fElapsedTime;
        if (dy + 10 > ScreenHeight()) {
            dy = orgDy;
        }
        if (dy < 0) {
            dy = orgDy;
        }
        if (dx + 10 > ScreenWidth()) {
            dx = orgDx;
        }
        if (dx < 0) {
            dx = orgDx;
        }
     // Collision(&dx, &dy, &orgDx, &orgDy);
     // DrawRectangle(dx, dy, dx + 10, dy + 10, FG_BLACK);
     // MakeBorders();
        for (auto cell : maze.grid)
        {
           

            if (cell->walls[Maze::CellWallDirs::top]) {
                DrawLine(cell->x * 20, cell->y * 20, cell->x * 20 + 20, cell->y * 20, FG_BLACK);
            }
            if (cell->walls[Maze::CellWallDirs::right]) {
                DrawLine(cell->x * 20 + 20, cell->y * 20, cell->x * 20 + 20, cell->y * 20+20, FG_BLACK);
            }
            if (cell->walls[Maze::CellWallDirs::bottom]) {
                DrawLine(cell->x * 20, cell->y * 20+20, cell->x * 20 + 20, cell->y * 20+20, FG_BLACK);
            }
            if (cell->walls[Maze::CellWallDirs::left]) {
                DrawLine(cell->x * 20+20, cell->y * 20+20, cell->x * 20 + 20, cell->y * 20+20,FG_BLACK);
            }
        }

        return 1;
    }

};
int main()
{
  Game GameConsole;

    GameConsole.ConstructConsole(200,200,4, 4);
    GameConsole.Start();
}
