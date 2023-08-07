#include "Game.h"
#include "Tests/FrameworkTest.h"
#include "Tests/GenericCollectionTest.h"

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        BITGame::Game::Instance().BuildLevel();
        BITGame::Game::Instance().Play();
        return 0;
    }
    if (argc == 3)
    {
        if (argv[1][0] == 't')
        {
            if (argv[2][0] == 'c')
                BITFramework::TestGenericCollection();
            if (argv[2][0] == 'f')
                BITFramework::TestFramework();
        }
        
    }
    

    return 0;
}
