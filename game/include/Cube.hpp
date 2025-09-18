#ifndef CUBE_HPP
#define CUBE_HPP

#include "raylib.h"
#include "nlohmann/json.hpp"
#include "Gizmo.hpp"

class Cube {
    public:
        Cube(Vector3 pos, float width, float height)
            : mPos(pos), mWidth(width), mHeight(height), mSelected(false) {}
        
        // Default constructor for deserialization
        Cube() : mPos({0, 0, 0}), mWidth(1.0f), mHeight(1.0f), mSelected(false) {}
        
        void Render();
        
        // Update method to handle gizmo interaction
        bool Update(Camera3D& camera);
        
        // Serialization methods
        nlohmann::json Serialize() const;
        void Deserialize(const nlohmann::json& json);
        
        // Static factory method for creating from JSON
        static Cube FromJson(const nlohmann::json& json);
        
        // Getters for accessing private members
        Vector3 GetPosition() const { return mPos; }
        float GetWidth() const { return mWidth; }
        float GetHeight() const { return mHeight; }
        
        // Selection methods
        void SetSelected(bool selected) { mSelected = selected; }
        bool IsSelected() const { return mSelected; }
        
        // Direct position setter
        void SetPosition(const Vector3& pos) { mPos = pos; }
        
    private:
        Vector3 mPos;
        float mWidth;
        float mHeight;
        bool mSelected;
        Gizmo mGizmo;
};


#endif