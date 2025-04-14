#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <iostream>
#include <queue>
#include <cassert>

#include "Types.hpp"


class EntityManager {
public:
    EntityManager() {
        for(Entity id = 0; id < MAX_ENTITIES; ++id) {
            availableIDs.push(id);
        }
    }

    Entity CreateEntity() {
        assert(livingEntityCount < MAX_ENTITIES && "Entity out of range!");
        
        Entity id = availableIDs.front();
        availableIDs.pop();
        ++ livingEntityCount;

        return id;
    }

    void DestroyEntity(Entity entity) {
        assert(livingEntityCount < MAX_ENTITIES && "Entity out of range!");

        signatures[entity].reset();
        availableIDs.push(entity);
        --livingEntityCount;
    }

    void SetSigniture(Entity entity, Signature signiture) {
        assert(livingEntityCount < MAX_ENTITIES && "Entity out of range!");
        signatures[entity] = signiture;     
    }

    Signature GetSignature(Entity entity) {
        assert(livingEntityCount < MAX_ENTITIES && "Entity out of range!");
        return signatures[entity];
    }

private:
    std::queue<Entity> availableIDs{};
    std::array<Signature, MAX_ENTITIES> signatures{};
    uint32_t livingEntityCount{};

};

#endif