#include "BITGameCommon.h"
#include "Game.h"
#include "Grid.h"

int main(int argc, char* argv[])
{
    BITGame::Game::Instance().BuildLevel();
    BITGame::Game::Instance().Play();

    return 0;
}
