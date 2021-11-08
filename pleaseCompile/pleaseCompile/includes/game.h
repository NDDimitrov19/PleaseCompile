#include <iostream>
#include <vector>
#include <memory>
#include "maze.h"
#include "olcPixelGameEngine.h"

#define WINDOW_WIDTH 200
#define WINDOW_HEIGHT 200
#define PIXEL_SIZE 4

class Game : public olc::PixelGameEngine
{
public:
    Game();
private:
    struct Colors
    {
        olc::Pixel background;
        olc::Pixel walls;
        olc::Pixel player;
        olc::Pixel start;
        olc::Pixel end;
        olc::Pixel textColor;
        olc::Pixel highLightedColor;
    } scheme;

    struct Player {
        float x;
        float y;
        float speed;
        float size;
    } player;

    olc::Sprite* sprPlayer;
    olc::Decal* decPlayer;

    struct coords
    {
        int x;
        int y;
    };

    std::vector< std::pair<coords, coords> > wallCoords;
    
    Maze maze;

    int mazeSize[2];
    int mazeWallSize;
    int nLayerBackground;

    void handleMenu();
    bool Menu();
    bool MenuPlay();
    bool MenuCredits();
    bool MenuHow();
    bool MenuEndGame();

    void createMazeData();
    void createBackgroundLayer();
    void initMazeData();

    bool isColliding(float playerX, float playerY, float playerSize);
    void handleInput(float fElapsedTime);

    void drawStartFinish();
    void winChecker();

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

};