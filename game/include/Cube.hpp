#ifndef CUBE_HPP
#define CUBE_HPP

#include "raylib.h"
#include "nlohmann/json.hpp"

class Cube {
    public:
        Cube(Vector3 pos, float width, float height)
            : mPos(pos), mWidth(width), mHeight(height) {}
        
        // Default constructor for deserialization
        Cube() : mPos({0, 0, 0}), mWidth(1.0f), mHeight(1.0f) {}
        
        void Render();
        
        // Serialization methods
        nlohmann::json Serialize() const;
        void Deserialize(const nlohmann::json& json);
        
        // Static factory method for creating from JSON
        static Cube FromJson(const nlohmann::json& json);
        
        // Getters for accessing private members
        Vector3 GetPosition() const { return mPos; }
        float GetWidth() const { return mWidth; }
        float GetHeight() const { return mHeight; }
        
    private:
        Vector3 mPos;
        float mWidth;
        float mHeight;
};


#endif