#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#include <raylib.h>

#include "engine.h"

void UpdateDrawFrame();

Engine* engine = new Engine();
void SetupWindow();

int main()
{
	SetRandomSeed(42);

	// set up the window
	InitWindow((int)GLOBALS::SCREEN.x, (int)GLOBALS::SCREEN.y, GLOBALS::project_name.c_str());

	//PrintMemoryUsage();
	engine->Init();

#if defined(PLATFORM_WEB)
	emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
	SetTargetFPS(60); // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		engine->Update();

		engine->Render();
	}
#endif

	engine->Shutdown();
	delete(engine);

	CloseWindow();
	return 0;
}

void UpdateDrawFrame()
{
	
	if (IsKeyDown(KEY_Q))
	{
		CloseWindow();
		return;
	}

	engine->Update();
	engine->Render();
}

void SetupWindow() {
	SetTargetFPS(60);

	Image icon = LoadImage("../assets/icons/window_icon.png");

	ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

	SetWindowIcon(icon);

	UnloadImage(icon);
}