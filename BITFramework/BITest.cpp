
#include <iostream>

#include "GenericCollectionTest.h"
#include "Component/Custom/Position.h"
#include "Entity/Core/EntityManager.h"
#include "Object/EntityAction/Custom/InitMover.h"
#include "Object/EntityAction/Custom/MoveInDirection.h"

int main(int argc, char* argv[])
{
    using namespace BITFramework;
    
    // auto e = EntityManager::Instance().CreateEntity();
    //
    // std::cout << *e << '\n';

    //TestGenericCollection();

    auto& e1 = EntityManager::Instance().CreateEntity();
    auto& mover1 = EntityAction::Create<InitMover>(e1, vec3(0, 0, 0), vec3::right());

    auto& e2 = EntityManager::Instance().CreateEntity();
    auto& mover2 = EntityAction::Create<InitMover>(e2, vec3(0, 0, 0), vec3::down());
    
    mover1.Update(1);
    mover1.Update(1);
    mover1.Update(1);

    mover2.Update(1);
    mover2.Update(1);
    mover2.Update(1);


    return 0;
}
