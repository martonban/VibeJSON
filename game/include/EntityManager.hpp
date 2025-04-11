#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <iostream>
#include <queue>

#include "Types.hpp"

class EntityManager {
public:
    EntityManager() {
        for(Entity id = 0; id < MAX_ENTITIES; ++id) {
            available_ids.push(id);
        }
    }

private:
    std::queue<Entity> available_ids{};
};

#endif