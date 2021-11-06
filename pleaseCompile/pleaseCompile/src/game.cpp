#include "game.h"

void Game::DrawRectangle(int x1, int y1, int x2, int y2, short c) {
    DrawLine(x1, y1, x1, y2, PIXEL_SOLID, c);
    DrawLine(x1, y2, x2, y2, PIXEL_SOLID, c);
    DrawLine(x2, y2, x2, y1, PIXEL_SOLID, c);
    DrawLine(x2, y1, x1, y1, PIXEL_SOLID, c);
}

void Game::MovePlayer(float fElapsedTime) {
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


