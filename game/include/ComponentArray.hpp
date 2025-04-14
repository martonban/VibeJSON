#ifndef COMPONENT_ARRAY_HPP
#define COMPONENT_ARRAY_HPP

#include <cassert>

#include "Types.hpp"

class IComponenetArray {
    public:
        virtual ~IComponenetArray() = default;
        virtual void EntityDestroyed(Entity entity);    
};

template<typename T>
class ComponentArray : public IComponenetArray {
    public:
        void InsertData(Entitiy entity, T component) {
            assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && "Component added to same entity more than once.");            
            
            size_t newIndex = size;
            entityToIndexMap[entity] = newIndex;
            indexToEntityMap[newIndex] = entity;
            componentArray[newIndex] = component;
            ++size;
        }

        void RemoveData(Entity entity) {
            assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component.");
        }

    private:
	    std::array<T, MAX_ENTITIES> componentArray;
	    std::unordered_map<Entity, size_t> entityToIndexMap;
	    std::unordered_map<size_t, Entity> indexToEntityMap;
	    size_t size;
};

#endif