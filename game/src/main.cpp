#include "raylib.h"
#include "raymath.h"

#include <iostream>
#include <string>

#include "imgui.h"
#include "rlImGui.h"


// DPI scaling functions
float ScaleToDPIF(float value)
{
    return GetWindowScaleDPI().x * value;
}

int ScaleToDPII(int value)
{
    return int(GetWindowScaleDPI().x * value);
}



int main(int argc, char* argv[])
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 1280;
	int screenHeight = 800;

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "raylib-Extras [ImGui] example - simple ImGui Demo");
	SetTargetFPS(144);
	rlImGuiSetup(true);

	
	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);

		// start ImGui Conent
		rlImGuiBegin();

		// show ImGui Content
		bool open = true;
		ImGui::ShowDemoWindow(&open);

		open = true;
		float f;

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
		//----------------------------------------------------------------------------------
	}
	rlImGuiShutdown();

	// De-Initialization
	//--------------------------------------------------------------------------------------   
    rlImGuiShutdown();
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}