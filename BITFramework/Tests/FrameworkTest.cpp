#include "bitpch.h"
#include "FrameworkTest.h"

#include "helpers.h"
#include "Entity/Core/EntityManager.h"
#include "Object/EntityAction/Core/EntityAction.h"
#include "Object/EntityAction/Custom/MoveInDirection.h"
#include "Entity/Core/Entity.h"
#include "Object/EntityAction/Custom/Collide.h"
#include "Object/EntityAction/Custom/InitMover.h"

void BITFramework::TestFramework()
{
    // create an entity
    std::weak_ptr<Entity> entityPtr = EntityManager::Instance().CreateEntity();
    // we're using weak_ptr as mean of observing lifetime of the entity.

    assert(!entityPtr.expired());
    std::cout << "Entity created:\n" << *entityPtr.lock() << std::endl;
    
    // create an entity action and add it to the entity
    Entity& entity = *entityPtr.lock(); // we lock the weak_ptr and use more convenient reference
    EntityAction::Create<MoveInDirection>(entity, vec3::right());
    
    std::cout << "\nEntity action added:\n" << entity << std::endl;
    
    auto objPacked = entity.getActionManager().GetObject<MoveInDirection>();
    assert(objPacked.has_value());
    // we return object again as weak_ptr, since it can be removed and because it might not be on the entity,
    // we return optional
    auto& moveInDirectionAction = *objPacked.value().lock();
    moveInDirectionAction.SetDirection(vec3::left());
    std::cout << "\nEntity action changed:\n" << entity << std::endl;
    
    // create an entity action that adds another entity action and adds it to the entity
    std::weak_ptr<Entity> entity2Ptr = EntityManager::Instance().CreateEntity();
    Entity& entity2 = *entity2Ptr.lock();
    EntityAction::Create<InitMover>(entity2, vec3{5,5,5}, vec3::down());
    auto initMoverPacked = entity2.getActionManager().GetObject<InitMover>();
    assert(initMoverPacked.has_value());
    std::cout << "\nEntity action added:\n" << entity2 << std::endl;
    
    // remove an action from the entity action manager
    entity2.getActionManager().UnregisterObject(initMoverPacked.value().lock());
    assert(initMoverPacked.value().expired());
    assert(!entity2.getActionManager().GetObject<InitMover>().has_value());
    std::cout << "\nEntity action removed:\n" << entity2 << std::endl;
    
    // invoke custom function on the entity action
    entity2.getActionManager().InvokeAll(&MoveInDirection::SetDirection, vec3::up());
    assert(entity2.getActionManager().GetObject<MoveInDirection>().value().lock()->GetDirection() == vec3::up());
    std::cout << "\nEntity action custom function invoked:\n" << entity2 << std::endl;

    // get all visible actions
    EntityAction::Create<Collide>(entity2, 1.0f);
    auto collidePacked = entity2.getActionManager().GetObject<Collide>();
    assert(collidePacked.has_value());
    auto& collideAction = *collidePacked.value().lock();
    auto actions = entity2.getActionManager().GetVisibleActions();
    assert(actions.size() == 2);
    std::cout << "\nEntity Actions:"<< entity2 << '\n';
    // set action to not visible
    collideAction.SetVisible(false);
    std::cout << "Action set to not visible" << std::endl;
    std::cout << "\nEntity Actions:"<< entity2 << '\n';
    // get all visible actions again
    actions = entity2.getActionManager().GetVisibleActions();
    assert(actions.size() == 1);

    // remove an Entity
    EntityManager::Instance().DeleteEntity(entityPtr.lock().get());
    EntityManager::Instance().Update();
    assert(entityPtr.expired());
}
