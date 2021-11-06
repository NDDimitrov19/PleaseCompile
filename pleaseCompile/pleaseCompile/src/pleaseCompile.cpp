#include <iostream>
#include <vector>
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

    void DrawRectangle(int x1, int y1, int x2, int y2, short c) {
        DrawLine(x1, y1, x1, y2, PIXEL_SOLID, c);
        DrawLine(x1, y2, x2, y2, PIXEL_SOLID, c);
        DrawLine(x2, y2, x2, y1, PIXEL_SOLID, c);
        DrawLine(x2, y1, x1, y1, PIXEL_SOLID, c);
    }
    void MovePlayer(float fElapsedTime) {

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
        return 1;
    }
    
    virtual bool OnUserUpdate(float fElapsedTime) {

     Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_GREEN);

     DrawRectangle(PlayerX, PlayerY, PlayerX + 10, PlayerY + 10, FG_BLACK);
     std::string PlayerDirection;
     if (m_keys[L'W'].bHeld || m_keys[VK_UP].bHeld)
         PlayerDirection = "up";
     if (m_keys[L'D'].bHeld || m_keys[VK_RIGHT].bHeld)
         PlayerDirection = "right";
     if (m_keys[L'S'].bHeld || m_keys[VK_DOWN].bHeld)
         PlayerDirection = "down";
     if (m_keys[L'A'].bHeld || m_keys[VK_LEFT].bHeld)
         PlayerDirection = "left";

     if (PlayerDirection == "up") {
         PlayerY -= (float)PlayerSpeed * fElapsedTime;
     }
     if (PlayerDirection == "right") {
         PlayerX += (float)PlayerSpeed *fElapsedTime;
     }
     if (PlayerDirection == "down") {
         PlayerY += (float)PlayerSpeed * fElapsedTime;
     }
     if (PlayerDirection == "left") {
         PlayerX -= (float)PlayerSpeed * fElapsedTime;
     }
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
