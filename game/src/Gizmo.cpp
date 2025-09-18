#include "Gizmo.hpp"

Gizmo::Gizmo() 
    : mEnabled(true)
    , mArrowLength(1.0f)
    , mArrowThickness(0.03f)
    , mHandleSize(0.1f)
    , mDraggingX(false)
    , mDraggingY(false)
    , mDraggingZ(false)
    , mLastMousePos({0, 0}) 
{
    // Initialize gizmo with good default values that are visually appealing
}

void Gizmo::Render(const Vector3& position) {
    if (!mEnabled) return;

    // Colors for axes (enhanced for better visibility)
    Color xColor = mDraggingX ? YELLOW : RED;       // X axis: Red (Yellow when dragging)
    Color yColor = mDraggingY ? YELLOW : GREEN;     // Y axis: Green (Yellow when dragging)
    Color zColor = mDraggingZ ? YELLOW : BLUE;      // Z axis: Blue (Yellow when dragging)

    // X axis (red)
    DrawCylinderEx(
        position, 
        Vector3Add(position, {mArrowLength * 0.9f, 0, 0}),
        mArrowThickness,
        mArrowThickness,
        8,
        xColor
    );
    
    // X axis arrow head (cone)
    Vector3 xStart = Vector3Add(position, {mArrowLength * 0.9f, 0, 0});
    Vector3 xEnd = Vector3Add(position, {mArrowLength, 0, 0});
    DrawCylinderEx(
        xStart,
        xEnd,
        mArrowThickness * 2.5f, // Base
        0.0f,                   // Tip (pointed)
        8,
        xColor
    );
    
    // X axis handle (sphere) with outline for better visibility
    Vector3 xHandlePos = Vector3Add(position, {mArrowLength, 0, 0});
    DrawSphere(xHandlePos, mHandleSize, xColor);
    DrawSphereWires(xHandlePos, mHandleSize, 8, 8, BLACK);

    // Y axis (green)
    DrawCylinderEx(
        position, 
        Vector3Add(position, {0, mArrowLength * 0.9f, 0}),
        mArrowThickness,
        mArrowThickness,
        8,
        yColor
    );
    
    // Y axis arrow head
    Vector3 yStart = Vector3Add(position, {0, mArrowLength * 0.9f, 0});
    Vector3 yEnd = Vector3Add(position, {0, mArrowLength, 0});
    DrawCylinderEx(
        yStart,
        yEnd,
        mArrowThickness * 2.5f,
        0.0f,
        8,
        yColor
    );
    
    // Y axis handle (sphere) with outline
    Vector3 yHandlePos = Vector3Add(position, {0, mArrowLength, 0});
    DrawSphere(yHandlePos, mHandleSize, yColor);
    DrawSphereWires(yHandlePos, mHandleSize, 8, 8, BLACK);

    // Z axis (blue)
    DrawCylinderEx(
        position, 
        Vector3Add(position, {0, 0, mArrowLength * 0.9f}),
        mArrowThickness,
        mArrowThickness,
        8,
        zColor
    );
    
    // Z axis arrow head
    Vector3 zStart = Vector3Add(position, {0, 0, mArrowLength * 0.9f});
    Vector3 zEnd = Vector3Add(position, {0, 0, mArrowLength});
    DrawCylinderEx(
        zStart,
        zEnd,
        mArrowThickness * 2.5f,
        0.0f,
        8,
        zColor
    );
    
    // Z axis handle (sphere) with outline
    Vector3 zHandlePos = Vector3Add(position, {0, 0, mArrowLength});
    DrawSphere(zHandlePos, mHandleSize, zColor);
    DrawSphereWires(zHandlePos, mHandleSize, 8, 8, BLACK);
    
    // Draw small coordinate system at center
    float centerSize = mArrowThickness * 5.0f;
    DrawLine3D(position, Vector3Add(position, {centerSize, 0, 0}), RED);
    DrawLine3D(position, Vector3Add(position, {0, centerSize, 0}), GREEN);
    DrawLine3D(position, Vector3Add(position, {0, 0, centerSize}), BLUE);
}

bool Gizmo::CheckAxisHandleHit(const Ray& ray, const Vector3& position, const Vector3& axisDir) {
    // Get position of the handle (axis endpoint)
    Vector3 handlePos = Vector3Add(position, axisDir);
    
    // Implement our own ray-sphere intersection test
    Vector3 delta = Vector3Subtract(ray.position, handlePos);
    float a = Vector3DotProduct(ray.direction, ray.direction);
    float b = 2.0f * Vector3DotProduct(delta, ray.direction);
    float c = Vector3DotProduct(delta, delta) - mHandleSize * mHandleSize;
    
    // Calculate discriminant
    float discriminant = b * b - 4 * a * c;
    
    // If discriminant is negative, no intersection
    if (discriminant < 0) {
        return false;
    }
    
    // Calculate intersection distance
    float distance = (-b - sqrtf(discriminant)) / (2.0f * a);
    
    // If distance is negative, intersection is behind the ray origin
    return distance >= 0;
}

bool Gizmo::HandleInteraction(Camera3D& camera, Vector3& position) {
    if (!mEnabled) return false;
    
    bool positionChanged = false;
    Vector2 mousePos = GetMousePosition();
    
    // Check if ImGui is using the mouse - if so, don't process gizmo interactions
    if (ImGui::GetIO().WantCaptureMouse) {
        return false;
    }
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Cast a ray from the mouse position into the 3D scene
        Ray ray = GetMouseRay(mousePos, camera);
        
        // Check collision with each axis handle
        mDraggingX = CheckAxisHandleHit(ray, position, {mArrowLength, 0, 0});
        mDraggingY = CheckAxisHandleHit(ray, position, {0, mArrowLength, 0});
        mDraggingZ = CheckAxisHandleHit(ray, position, {0, 0, mArrowLength});
        
        mLastMousePos = mousePos;
    }
    
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        // Calculate mouse movement delta
        Vector2 mouseDelta = {mousePos.x - mLastMousePos.x, mousePos.y - mLastMousePos.y};
        
        // Apply movement based on which axis is being dragged
        float movementSpeed = 0.01f;
        
        // Scale speed based on distance from camera for better control
        float distanceToCamera = Vector3Distance(position, camera.position);
        movementSpeed *= (distanceToCamera / 10.0f); // Adjust this factor as needed
        
        if (mDraggingX) {
            // For X axis, use horizontal mouse movement
            position.x += mouseDelta.x * movementSpeed;
            positionChanged = true;
        }
        if (mDraggingY) {
            // For Y axis, use vertical mouse movement (reversed)
            position.y -= mouseDelta.y * movementSpeed;
            positionChanged = true;
        }
        if (mDraggingZ) {
            // For Z axis, use horizontal mouse movement for more intuitive control
            position.z += mouseDelta.x * movementSpeed;
            positionChanged = true;
        }
        
        mLastMousePos = mousePos;
    }
    
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        mDraggingX = false;
        mDraggingY = false;
        mDraggingZ = false;
    }
    
    return positionChanged;
}