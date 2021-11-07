#include "game.h"

Game::Game()
{
    mazeSize[0] = 10;
    mazeSize[1] = 10;
    maze = Maze(mazeSize[0], mazeSize[1]);
    mazeWallSize = WINDOW_HEIGHT / mazeSize[1];
    player = { (float)(mazeWallSize / 4), (float)(mazeWallSize / 4), 30.0f ,(float)(mazeWallSize / 2) };
    scheme = { olc::BLACK, olc::WHITE,olc::YELLOW,olc::RED , olc::GREEN };
}



void Game::createMazeData()
{
    // Add outer edges
    wallCoords.push_back({ {0, 0}, {ScreenWidth(), 0} });
    wallCoords.push_back({ {ScreenWidth() - 1, 0}, {ScreenWidth() - 1, ScreenHeight() - 1} });
    wallCoords.push_back({ {0, ScreenHeight() - 1}, {ScreenWidth() - 1, ScreenHeight() - 1} });
    wallCoords.push_back({ {0, 0}, {0, ScreenHeight() - 1} });

    // Add maze walls
    for (auto& cell : maze.grid)
    {
        if (cell.walls[Maze::CellWallDirs::top]) {
            this->wallCoords.push_back({ {cell.x * mazeWallSize, cell.y * mazeWallSize}, {cell.x * mazeWallSize + mazeWallSize, cell.y * mazeWallSize} });
        }
        if (cell.walls[Maze::CellWallDirs::right]) {
            this->wallCoords.push_back({ {cell.x * mazeWallSize + mazeWallSize, cell.y * mazeWallSize}, {cell.x * mazeWallSize + mazeWallSize, cell.y * mazeWallSize + mazeWallSize} });
        }
        // Optimization
        //if (cell.walls[Maze::CellWallDirs::bottom]) {
        //    this->wallCoords.push_back({ {cell.x * 20, cell.y * 20 + 20}, {cell.x * 20 + 20, cell.y * 20 + 20} });
        //}
        //if (cell.walls[Maze::CellWallDirs::left]) {
        //    this->wallCoords.push_back({ {cell.x * 20, cell.y * 20}, {cell.x * 20, cell.y * 20 + 20} });
        //}
    }
}

bool Game::isColliding(float playerX, float playerY, float playerSize)
{
    for (auto& wall : wallCoords)
    {
        bool xCheck = false;
        bool yCheck = false;
        //if Horizontal wall
        if (wall.first.y == wall.second.y)
        {
            if (playerX - 1 <= wall.second.x && playerX + playerSize >= wall.first.x)
                xCheck = true;

            if (playerY - 1 <= wall.first.y && playerY + playerSize >= wall.first.y)
                yCheck = true;


        }
        //if Vertical wall
        else if (wall.first.x == wall.second.x)
        {
            if (playerX - 1 <= wall.first.x && playerX + playerSize >= wall.first.x)
                xCheck = true;

            if (playerY - 1 <= wall.second.y && playerY + playerSize >= wall.first.y)
                yCheck = true;
        }

        if (xCheck && yCheck)
            return true;
    }

    return false;
}

void Game::handleInput(float fElapsedTime)
{
    short movementX = 0;
    short movementY = 0;
    float speedBoost = 1.0f;

    // Cheats 
    speedBoost = GetKey(olc::Key::SHIFT).bHeld ? 2.54f : 1.0f;

    if (GetKey(olc::Key::R).bPressed)
    {
        player.x = (float)(mazeWallSize / 4);
        player.y = (float)(mazeWallSize / 4);
    }

    if (GetKey(olc::Key::W).bHeld || GetKey(olc::Key::UP).bHeld)
    {
        if(!isColliding(player.x,player.y-1, player.size))
           movementY = -1;
    }
    if (GetKey(olc::Key::D).bHeld || GetKey(olc::Key::RIGHT).bHeld)
    {
        if (!isColliding(player.x + 1, player.y, player.size))
            movementX = 1;
    }
    if (GetKey(olc::Key::S).bHeld || GetKey(olc::Key::DOWN).bHeld)
    {
        if (!isColliding(player.x, player.y + 1, player.size))
            movementY = 1;
    }
    if (GetKey(olc::Key::A).bHeld || GetKey(olc::Key::LEFT).bHeld)
    {
        if (!isColliding(player.x - 1, player.y, player.size))
            movementX = -1;
    }
    if ((movementX == 1 && movementY == 1) || (movementX == -1 && movementY == -1) || (movementX == 1 && movementY == -1) || (movementX == -1 && movementY == 1))
    {
        player.x += movementX * player.speed * speedBoost * fElapsedTime / 2;
        player.y += movementY * player.speed * speedBoost * fElapsedTime / 2;
    }
    else
    {
        player.x += movementX * player.speed * speedBoost * fElapsedTime;
        player.y += movementY * player.speed * speedBoost * fElapsedTime;
    }

}

void Game::drawStartFinish()
{
    FillRect(1, 1, mazeWallSize, mazeWallSize, scheme.start);
    FillRect(ScreenWidth() - mazeWallSize + 1, ScreenHeight() - mazeWallSize + 1, mazeWallSize, mazeWallSize, scheme.end);
}

bool Game::OnUserCreate()  
{
    // Set up maze background layer
    createMazeData();

    nLayerBackground = CreateLayer();
    SetDrawTarget(nLayerBackground);

    Clear(scheme.background);
    drawStartFinish();
    for (auto& wall : this->wallCoords)
    {
        DrawLine(wall.first.x, wall.first.y, wall.second.x, wall.second.y, scheme.walls);
    }

    EnableLayer(nLayerBackground, true);
    SetDrawTarget(nullptr);

    return 1;
}

bool Game::OnUserUpdate(float fElapsedTime)  
{
        Clear(olc::BLANK);

        handleInput(fElapsedTime);
        DrawRect(player.x, player.y, player.size, player.size, scheme.player);

        return 1;
}
