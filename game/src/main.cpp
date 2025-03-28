#include "raylib.h"
#include "raymath.h"

#include <iostream>
#include <string>

#include "imgui.h"
#include "rlImGui.h"


/*-------------------------------------------------------------------------------------------------------------------------------
*                                          	NebulaPax - SpaceOS
*                                      	Copyright (c) Márton Bán 2025
*	SpaceOS is powered by the NebulaPax engine. This engine evolves iteratively, with each new game representing a new
*	version of the engine, continuously improving and expanding its capabilities.
*-------------------------------------------------------------------------------------------------------------------------------
*/


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
	int screenWidth = 1280;
	int screenHeight = 800;

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "raylib-Extras [ImGui] example - simple ImGui Demo");
	SetTargetFPS(144);
	rlImGuiSetup(true);

	Camera3D camera = { 0 };
	camera.position = Vector3{ 4.0f, 4.0f, 4.0f };
	camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;                         
	camera.projection = CAMERA_PERSPECTIVE;
	EndTextureMode();
    RenderTexture2D frame_renderer = LoadRenderTexture(screenWidth, screenHeight);
	float f = 0.f;
	

	while (!WindowShouldClose()) {
		rendering(camera, frame_renderer);

		BeginDrawing();
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
				std::cout << "pénisz";
			}
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		}
		ImGui::End();
		std::cout << std::endl << f << std::endl;

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