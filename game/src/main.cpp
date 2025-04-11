#include <iostream>
#include <string>

#include "raylib.h"
#include "raymath.h"

#include "imgui.h"
#include "rlImGui.h"


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

void rendering(Camera3D& camera, RenderTexture2D& target) {
	BeginTextureMode(target);
	ClearBackground(RAYWHITE);
	BeginMode3D(camera);
	DrawCube(Vector3{0.f,0.f,0.f}, 1.0f, 1.0f, 1.0f, RED);
  	UpdateCamera(&camera, CAMERA_THIRD_PERSON); 
	EndMode3D();
	EndTextureMode();
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
		ImGui::ShowDemoWindow(&open);

		open = true;


		if (ImGui::Begin("Test Window", &open))
		{
			ImGui::Text("Hello, world %d", 123);
			if (ImGui::Button("Save")) {
				std::cout << "Test";
			}
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		}
		ImGui::End();

		// end ImGui Content
		rlImGuiEnd();
		EndDrawing();
		std::cout << GetFPS() << std::endl;
	}
	UnloadRenderTexture(frame_renderer);
	rlImGuiShutdown();
 
    rlImGuiShutdown();
	CloseWindow();
	return 0;
}
