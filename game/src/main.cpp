#include <iostream>
#include <fstream>

#include "raylib.h"
#include "raymath.h"

#include "imgui.h"
#include "rlImGui.h"

#include "Cube.hpp"




//-------------------------------------------------------------------------------------------------------------------------------*                                          	
//												NebulaPax - SpaceOS
//                                      	Copyright (c) Márton Bán 2025
//	SpaceOS is powered by the NebulaPax engine. This engine evolves iteratively, with each new game representing a new
//	version of the engine, continuously improving and expanding its capabilities.
//-------------------------------------------------------------------------------------------------------------------------------

// DPI scaling functions

float ScaleToDPIF(float value) {
    return GetWindowScaleDPI().x * value;
}

int ScaleToDPII(int value) {
    return int(GetWindowScaleDPI().x * value);
}

void rendering(Camera3D& camera, RenderTexture2D& target);
Cube cube = { Vector3{0.0f, 0.0f, 0.0f}, 1.0f, 1.0f};

// Global variables for the application state
bool showAddMenu = false;
bool editMode = true; // Start with edit mode enabled

// Dummy functions for object creation
void CreateCube() {
    std::cout << "Creating Cube..." << std::endl;
    // TODO: Implement cube creation
}

void CreateSphere() {
    std::cout << "Creating Sphere..." << std::endl;
    // TODO: Implement sphere creation
}

void CreateTestModel() {
    std::cout << "Creating Test Model..." << std::endl;
    // TODO: Implement test model creation
}

int main(int argc, char* argv[]) {
	int SCREEN_WIDTH = 1280;
	int SCREEN_HEIGHT = 800;

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib-Extras [ImGui] example - simple ImGui Demo");
	SetTargetFPS(60);
	rlImGuiSetup(true);

	Camera3D camera = { 0 };
	camera.position = Vector3{ 4.0f, 4.0f, 4.0f };
	camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;                         
	camera.projection = CAMERA_PERSPECTIVE;

    RenderTexture2D frame_renderer = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
	float f = 0.f;
	

	while (!WindowShouldClose()) {
		// Check for Shift+A key combination
		if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_A)) {
			showAddMenu = !showAddMenu;
		}
		
		// Camera rotation with middle mouse button
		if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON) && !ImGui::GetIO().WantCaptureMouse) {
			Vector2 mouseDelta = GetMouseDelta();
			
			// Rotate the camera around the target
			float cameraRotSpeed = 0.003f;
			
			// Calculate camera position in spherical coordinates
			Vector3 toCamera = Vector3Subtract(camera.position, camera.target);
			float distance = Vector3Length(toCamera);
			float theta = atan2f(toCamera.z, toCamera.x);
			float phi = acosf(toCamera.y / distance);
			
			// Update theta and phi based on mouse movement
			theta -= mouseDelta.x * cameraRotSpeed;
			phi -= mouseDelta.y * cameraRotSpeed;
			
			// Clamp phi to avoid camera flipping
			phi = Clamp(phi, 0.1f, PI - 0.1f);
			
			// Convert back to cartesian coordinates
			camera.position.x = camera.target.x + distance * cosf(theta) * sinf(phi);
			camera.position.y = camera.target.y + distance * cosf(phi);
			camera.position.z = camera.target.z + distance * sinf(theta) * sinf(phi);
		}
		
		// Camera zoom with mouse wheel
		float mouseWheel = GetMouseWheelMove();
		if (mouseWheel != 0 && !ImGui::GetIO().WantCaptureMouse) {
			Vector3 toCamera = Vector3Subtract(camera.position, camera.target);
			float distance = Vector3Length(toCamera);
			
			// Zoom in/out
			float zoomSpeed = 0.2f;
			distance -= mouseWheel * zoomSpeed * distance;
			distance = Clamp(distance, 1.0f, 50.0f); // Prevent zooming too close or too far
			
			// Normalize the direction vector
			toCamera = Vector3Scale(Vector3Normalize(toCamera), distance);
			camera.position = Vector3Add(camera.target, toCamera);
		}
		
		// Handle selection and deselection only when not interacting with gizmos
		bool handledByGizmo = false;
		if (editMode && cube.IsSelected()) {
			handledByGizmo = cube.Update(camera);
		}
		
		// Check for clicking on the cube to select it (only if not handled by gizmo)
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !ImGui::GetIO().WantCaptureMouse && !handledByGizmo) {
			// Get the ray from the mouse position
			Ray ray = GetMouseRay(GetMousePosition(), camera);
			
			// Create a bounding box for the cube
			BoundingBox cubeBox = {
				Vector3Subtract(cube.GetPosition(), {cube.GetWidth()/2, cube.GetHeight()/2, 0.5f}),
				Vector3Add(cube.GetPosition(), {cube.GetWidth()/2, cube.GetHeight()/2, 0.5f})
			};
			
			// Check for collision with the cube using GetRayCollisionBox
			RayCollision collision = GetRayCollisionBox(ray, cubeBox);
			
			// If collision occurred
			if (collision.hit) {
				// Select the cube
				cube.SetSelected(true);
			} else {
				// If clicking outside, deselect the cube
				cube.SetSelected(false);
			}
		}
		
		BeginDrawing();
		rendering(camera, frame_renderer);
        DrawTextureRec(frame_renderer.texture, Rectangle{0, 0, (float)frame_renderer.texture.width, -(float)frame_renderer.texture.height}, Vector2{0, 0}, WHITE);
		
		// start ImGui Conent
		rlImGuiBegin();

		// show ImGui Content
		bool open = true;


		if (ImGui::Begin("Test Window", &open))
		{
			ImGui::Text("Hello, world %d", 123);
			
			// Help box for controls
			if (ImGui::CollapsingHeader("Camera Controls Help", ImGuiTreeNodeFlags_DefaultOpen)) {
				ImGui::BulletText("Middle Mouse Button: Rotate Camera");
				ImGui::BulletText("Mouse Wheel: Zoom In/Out");
				ImGui::BulletText("Left Click: Select/Deselect Cube");
				ImGui::BulletText("Drag Gizmo Arrows: Move Cube");
				ImGui::Separator();
			}
			
			// Edit mode toggle
			if (ImGui::Checkbox("Edit Mode (Gizmos)", &editMode)) {
				// If turning off edit mode, deselect the cube
				if (!editMode) {
					cube.SetSelected(false);
				}
			}
			
			// Selection status
			ImGui::Text("Cube Selected: %s", cube.IsSelected() ? "Yes" : "No");
			
			// Cube position controls
			Vector3 pos = cube.GetPosition();
			float position[3] = {pos.x, pos.y, pos.z};
			if (ImGui::SliderFloat3("Cube Position", position, -10.0f, 10.0f)) {
				// We can now use the setter instead of creating a new cube
				cube.SetPosition({position[0], position[1], position[2]});
			}
			
			// Cube dimension controls
			float width = cube.GetWidth();
			float height = cube.GetHeight();
			bool changed = false;
			if (ImGui::SliderFloat("Width", &width, 0.1f, 5.0f)) changed = true;
			if (ImGui::SliderFloat("Height", &height, 0.1f, 5.0f)) changed = true;
			
			if (changed) {
				cube = Cube(cube.GetPosition(), width, height);
				// Maintain selection state when recreating the cube
				cube.SetSelected(true);
			}
			
			ImGui::Separator();
			
			// Serialization controls
			if (ImGui::Button("Save Cube to JSON")) {
				nlohmann::json cubeJson = cube.Serialize();
				std::ofstream file("cube_save.json");
				file << cubeJson.dump(4);
				file.close();
				std::cout << "Cube saved to cube_save.json" << std::endl;
			}
			
			ImGui::SameLine();
			
			if (ImGui::Button("Load Cube from JSON")) {
				std::ifstream file("cube_save.json");
				if (file.is_open()) {
					nlohmann::json cubeJson;
					file >> cubeJson;
					file.close();
					cube = Cube::FromJson(cubeJson);
					std::cout << "Cube loaded from cube_save.json" << std::endl;
				} else {
					std::cout << "Could not open cube_save.json" << std::endl;
				}
			}
			
		}
		ImGui::End();

		// Add Menu - appears when Shift+A is pressed
		if (showAddMenu) {
			ImGui::SetNextWindowPos(ImVec2(200, 200), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize(ImVec2(200, 150), ImGuiCond_FirstUseEver);
			
			if (ImGui::Begin("Add Object", &showAddMenu, ImGuiWindowFlags_NoResize)) {
				ImGui::Text("Select object to add:");
				ImGui::Separator();
				
				if (ImGui::Button("Kocka", ImVec2(-1, 30))) {
					CreateCube();
					showAddMenu = false; // Close menu after selection
				}
				
				if (ImGui::Button("Gömb", ImVec2(-1, 30))) {
					CreateSphere();
					showAddMenu = false; // Close menu after selection
				}
				
				if (ImGui::Button("Test Modell", ImVec2(-1, 30))) {
					CreateTestModel();
					showAddMenu = false; // Close menu after selection
				}
			}
			ImGui::End();
		}

		// end ImGui Content
		rlImGuiEnd();
		EndDrawing();
	}
	UnloadRenderTexture(frame_renderer);
	rlImGuiShutdown();
 
    rlImGuiShutdown();
	CloseWindow();
	return 0;
}

void rendering(Camera3D& camera, RenderTexture2D& target) {
	BeginTextureMode(target);
	ClearBackground(RAYWHITE);
	BeginMode3D(camera);
	
	// Draw the grid for better spatial awareness
	DrawGrid(10, 1.0f);
	
	// Render cube and its gizmos if selected
	cube.Render();
	
	EndMode3D();
	EndTextureMode();
}
