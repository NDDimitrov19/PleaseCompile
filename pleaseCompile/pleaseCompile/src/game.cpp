#include "game.h"

void Game::MovePlayer(float fElapsedTime) 
{
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

bool Game::OnUserCreate()  
{
    for (auto& cell : maze.grid)
    {
        if (cell.walls[Maze::CellWallDirs::top]) {
            this->wallCoords.push_back({ {cell.x * mazeWallSize, cell.y * mazeWallSize}, {cell.x * mazeWallSize + mazeWallSize, cell.y * mazeWallSize} });
        }
        if (cell.walls[Maze::CellWallDirs::right]) {
            this->wallCoords.push_back({ {cell.x * mazeWallSize + mazeWallSize, cell.y * mazeWallSize}, {cell.x * mazeWallSize + mazeWallSize, cell.y * mazeWallSize + mazeWallSize} });
        }
        // Optimization
        //if (cell->walls[Maze::CellWallDirs::bottom]) {
        //    this->wallCoords.push_back({ {cell->x * 20, cell->y * 20 + 20}, {cell->x * 20 + 20, cell->y * 20 + 20} });
        //}
        //if (cell->walls[Maze::CellWallDirs::left]) {
        //    this->wallCoords.push_back({ {cell->x * 20, cell->y * 20}, {cell->x * 20, cell->y * 20 + 20} });
        //}
    }

    nLayerBackground = CreateLayer();
    SetDrawTarget(nLayerBackground);
    for (auto& wall : this->wallCoords)
    {
        DrawLine(wall.first.x, wall.first.y, wall.second.x, wall.second.y, olc::WHITE);
    }
    DrawRect(0, 0, ScreenWidth() - 1, ScreenHeight() - 1, olc::WHITE);
    EnableLayer(nLayerBackground, true);
    SetDrawTarget(nullptr);
    return 1;
}

bool Game::OnUserUpdate(float fElapsedTime)  
{
        Clear(olc::BLANK);

        MovePlayer(fElapsedTime);
        DrawRect(player.x, player.y, mazeWallSize / 2, mazeWallSize / 2, olc::YELLOW);
        // DrawCircle(player.x, player.y, 5, olc::BLACK);

        return 1;
}
