#include "menu.h"

Menu::Menu() 
{

}

Menu::~Menu()
{

}

void Menu::PleaseDraw(olc::PixelGameEngine* pge)
{
    pge->DrawString({ 100,100 }, "Menu", olc::WHITE);
}