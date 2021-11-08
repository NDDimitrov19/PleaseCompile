#include "game.h"
#include <string>

Game::Game()
{
    mazeSize[0] = 10;
    mazeSize[1] = 10;
    scheme = { olc::BLACK, olc::WHITE,olc::WHITE,olc::RED , olc::GREEN, olc::WHITE, olc::RED };
}

int menuOption = 0;
bool gameStarted = false;
bool backgroundCreated = false;

void Game::initMazeData()
{
    maze = Maze(mazeSize[0], mazeSize[1]);
    mazeWallSize = WINDOW_HEIGHT / mazeSize[1];
    player = { (float)(mazeWallSize / 4), (float)(mazeWallSize / 4), 30.0f ,(float)(mazeWallSize / 2) };
}

void Game::handleMenu()
{
    switch (menuOption) {
    case 0:
        Menu();
        break;
    case 1:
        MenuPlay();
        break;
    case 2:
        MenuHow();
        break;
    case 3:
        MenuCredits();
    }
}

bool Game::Menu() 
{
    //DrawString({ 0,0 }, std::to_string(GetMouseX()));
    //DrawString({ 0,20 }, std::to_string(GetMouseY()));
    DrawString({ 69,5 }, "Menu", scheme.textColor, 2U);

    if (GetMouseX() > 20 && GetMouseY() > 50 && GetMouseX() < 100 && GetMouseY() < 60)
    {
        DrawString({ 20,50 }, "Play", scheme.highLightedColor, 1U);
        if (GetMouse(0).bPressed)
        {
            menuOption=1; return true;
        }
    }
    else
    {
        DrawString({ 20,50 }, "Play", scheme.textColor, 1U);
    }

    if (GetMouseX() > 20 && GetMouseY() > 70 && GetMouseX() < 140 && GetMouseY() < 80)
    {
        DrawString({ 20,70 }, "How to play", scheme.highLightedColor, 1U);
        if (GetMouse(0).bPressed)
        {
            menuOption = 2; return true;
        }
    }
    else 
        DrawString({ 20,70 }, "How to play", scheme.textColor, 1U);

    if (GetMouseX() > 20 && GetMouseY() > 90 && GetMouseX() < 125 && GetMouseY() < 98)
    {
        DrawString({ 20,90 }, "Credits", scheme.highLightedColor, 1U);
        if (GetMouse(0).bPressed)
        {
            menuOption = 3; return true;
        }
    }
    else
        DrawString({ 20,90 }, "Credits", scheme.textColor, 1U);

    if (GetMouseX() > 20 && GetMouseY() > 110 && GetMouseX() < 131 && GetMouseY() < 117)
    {
        DrawString({ 20,110 }, "RageQuit", scheme.highLightedColor, 1U);
        if (GetMouse(0).bPressed)
        {
            menuOption = 4; return true;
        }
    }
    else
        DrawString({ 20,110 }, "RageQuit", scheme.textColor, 1U);
}

bool Game::MenuPlay()
{
   //DrawString({ 0,0 }, std::to_string(GetMouseX()));
   //DrawString({ 0,20 }, std::to_string(GetMouseY()));
    DrawString({ 20,5 }, "Difficulty", scheme.textColor, 2U);

    if (GetMouseX() > 20 && GetMouseY() > 50 && GetMouseX() < 100 && GetMouseY() < 60)
    {
        DrawString({ 20,50 }, "I'm too young to die", olc::CYAN, 1U);
        if (GetMouse(0).bPressed)
        {
            mazeSize[0] = 5;
            mazeSize[1] = 5;
            gameStarted = true;
            return false;
        }
    }
    else
        DrawString({ 20,50 }, "I'm too young to die", scheme.textColor, 1U);

    if (GetMouseX() > 20 && GetMouseY() > 70 && GetMouseX() < 140 && GetMouseY() < 80)
    {
        DrawString({ 20,70 }, "Hey, not too rough", olc::GREEN, 1U);
        if (GetMouse(0).bPressed)
        {
            mazeSize[0] = 10;
            mazeSize[1] = 10;
            gameStarted = true;
            return false;
        }
    }
    else
        DrawString({ 20,70 }, "Hey, not too rough", scheme.textColor, 1U);

    if (GetMouseX() > 20 && GetMouseY() > 90 && GetMouseX() < 125 && GetMouseY() < 98)
    {
        DrawString({ 20,90 }, "Hurt me plenty", olc::YELLOW, 1U);
        if (GetMouse(0).bPressed)
        {
            mazeSize[0] = 20;
            mazeSize[1] = 20;
            gameStarted = true;
            return false;
        }
    }
    else
        DrawString({ 20,90 }, "Hurt me plenty", scheme.textColor, 1U);

    if (GetMouseX() > 20 && GetMouseY() > 110 && GetMouseX() < 131 && GetMouseY() < 117)
    {
        DrawString({ 20,110 }, "Ultra-Violence", olc::VERY_DARK_RED, 1U);
        if (GetMouse(0).bPressed)
        {
            mazeSize[0] = 25;
            mazeSize[1] = 25;
            gameStarted = true;
            return false;
        }
    }
    else
        DrawString({ 20,110 }, "Ultra-Violence", scheme.textColor, 1U);

    if (GetMouseX() > 20 && GetMouseY() > 150 && GetMouseX() < 50 && GetMouseY() < 158)
    {
        DrawString({ 20,150 }, "Back", scheme.highLightedColor, 1U);
        if (GetMouse(0).bPressed)
        {
            menuOption = 0;
            return false;
        }
    }
    else
        DrawString({ 20,150 }, "Back", scheme.textColor, 1U);
}

bool Game::MenuHow()
{
    DrawString({ 69,0 }, "Guide", scheme.textColor, 2U);
    DrawString({ 50,30 }, "CONTROLS:", scheme.textColor, 1U);
    DrawString({ 50,50 }, "W A S D", olc::MAGENTA, 1U);
    DrawString({ 50,70 }, "Arrow Keys", olc::MAGENTA, 1U);
    DrawString({ 50,90 }, "Green => Win", olc::GREEN, 1U);

    if (GetMouseX() > 20 && GetMouseY() > 110 && GetMouseX() < 131 && GetMouseY() < 117)
    {
        DrawString({ 80,110 }, "Back", scheme.highLightedColor, 1U);
        if (GetMouse(0).bPressed)
        {
            menuOption = 0; return true;
        }
    }
    else
        DrawString({ 80,110 }, "Back", scheme.textColor, 1U);
}

bool Game::MenuCredits()
{
    //DrawString({ 0,0 }, std::to_string(GetMouseX()));
    //DrawString({ 0,20 }, std::to_string(GetMouseY()));
    DrawString({ 39,5 }, "Credits", scheme.textColor, 2U);
    DrawString({ 50,60 }, "Nikolai Dimitrov", scheme.textColor, 1U);
    DrawString({ 50,80 }, "Nikola Peshev", scheme.textColor, 1U);
    DrawString({ 50,100 }, "Stefan Ravninov", scheme.textColor, 1U);
    DrawString({ 50,120 }, "Egor Semenov", scheme.textColor, 1U);
    if (GetMouseX() > 20 && GetMouseY() > 140 && GetMouseX() < 110 && GetMouseY() < 147)
    {
        DrawString({ 80,140 }, "Back", scheme.highLightedColor, 1U);
        if (GetMouse(0).bPressed)
        {
            menuOption = 0; return true;
        }
    }
    else
        DrawString({ 80,140 }, "Back", scheme.textColor, 1U);
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

void Game::createBackgroundLayer()
{    
    //Set up maze background layer
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
    sprPlayer = new olc::Sprite("./resources/player.png");
    decPlayer = new olc::Decal(sprPlayer);

    return 1;
}

bool Game::OnUserUpdate(float fElapsedTime)  
{
    Clear(olc::BLANK);
    
    if (!backgroundCreated) 
    {
        if (menuOption == 4) return false;
        handleMenu();
    }
    if (gameStarted)
    {
        gameStarted = false;
        backgroundCreated = true;
        initMazeData();
        createBackgroundLayer();
    }
    if (backgroundCreated)
    {
        handleInput(fElapsedTime);
        DrawRect(player.x, player.y, player.size, player.size, scheme.player);
        DrawDecal({ player.x, player.y }, decPlayer, { 0.01f * (float)player.size, 0.01f * (float)player.size });
        std::cout << player.size << std::endl;
    }
    

    return 1;
}
