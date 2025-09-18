#ifndef GIZMO_HPP
#define GIZMO_HPP

#include "raylib.h"
#include "raymath.h"
#include "imgui.h"

// Forward declaration to avoid circular dependencies
class Cube;

// Class representing 3D manipulation gizmos
class Gizmo {
public:
    // Constructor
    Gizmo();
    
    // Render the gizmo arrows for a given position
    void Render(const Vector3& position);
    
    // Handle mouse interaction and return whether the position was changed
    bool HandleInteraction(Camera3D& camera, Vector3& position);
    
    // Enable/disable the gizmo
    void SetEnabled(bool enabled) { mEnabled = enabled; }
    bool IsEnabled() const { return mEnabled; }

private:
    bool mEnabled;              // Whether the gizmo is enabled
    float mArrowLength;         // Length of the gizmo arrows
    float mArrowThickness;      // Thickness of the gizmo arrows
    float mHandleSize;          // Size of the clickable handle
    
    bool mDraggingX;            // Whether X axis is being dragged
    bool mDraggingY;            // Whether Y axis is being dragged
    bool mDraggingZ;            // Whether Z axis is being dragged
    
    Vector2 mLastMousePos;      // Last mouse position for calculating movement

    // Check if a ray intersects with an axis handle
    bool CheckAxisHandleHit(const Ray& ray, const Vector3& position, const Vector3& axisDir);
};

#endif // GIZMO_HPP