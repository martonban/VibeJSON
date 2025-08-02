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

// Global variable for the add menu
bool showAddMenu = false;

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
			
			// Cube position controls
			Vector3 pos = cube.GetPosition();
			float position[3] = {pos.x, pos.y, pos.z};
			if (ImGui::SliderFloat3("Cube Position", position, -10.0f, 10.0f)) {
				cube = Cube(Vector3{position[0], position[1], position[2]}, cube.GetWidth(), cube.GetHeight());
			}
			
			// Cube dimension controls
			float width = cube.GetWidth();
			float height = cube.GetHeight();
			bool changed = false;
			if (ImGui::SliderFloat("Width", &width, 0.1f, 5.0f)) changed = true;
			if (ImGui::SliderFloat("Height", &height, 0.1f, 5.0f)) changed = true;
			
			if (changed) {
				cube = Cube(cube.GetPosition(), width, height);
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
	cube.Render();
	EndMode3D();
	EndTextureMode();
}
