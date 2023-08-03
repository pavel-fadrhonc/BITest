#include "BITGameCommon.h"
#include "Game.h"
#include "Grid.h"

int main(int argc, char* argv[])
{
    using namespace BITFramework;

    BITGame::Game::Instance().BuildLevel();
    BITGame::Game::Instance().Play();
    
    // auto& e1 = EntityManager::Instance().CreateEntity();
    // auto& mover1 = EntityAction::Create<InitMover>(e1, vec3(3, -3, 0), vec3::right());
    //
    // auto& e2 = EntityManager::Instance().CreateEntity();
    // auto& mover2 = EntityAction::Create<InitMover>(e2, vec3(0, -3, 0), vec3::down());
    //
    // //Grid grid(1, { vec3(-10, -10, -10), vec3(10, 10, 10)});
    // Grid grid(1, { vec3(-5, -5, -5), vec3(5, 5, 5)});
    // grid.AddEntity(e1, 'o');
    // //grid.AddEntity(e2, 'p');
    //
    // grid.Display();
    //
    // mover1.Update(1);
    // mover2.Update(1);
    //
    // grid.Display();
    //
    // mover1.Update(1);
    // mover2.Update(1);
    //
    // grid.Display();
    //
    // mover1.Update(1);
    // mover2.Update(1);
    //
    //
    // grid.Display();
    return 0;
}
