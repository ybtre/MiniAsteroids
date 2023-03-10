#pragma once

#include "gameoverlord.h"
#include "globals.h"
#include "entities.h"

class AEasingData{
public:
	int counter;
	int duration;
	Vector2 start;
	Vector2 end;
	Vector2 current;
};

class Engine
{
public:

	void Init();
	void Shutdown() const;
	void Update();
	void Render();

	void SetMainMenu();
	void SetGameOver();

	void UpdateMainMenu();
	void UpdateGameplay();
	void UpdateUpgradeScreen();
	void UpdateGameOver();

	void RenderMainMenu();
	void RenderGameplay();
	void RenderUpgradeScreen();
	void RenderGameOver();
	void RenderFadeTransition();

	bool is_shaking = false;
	float shake_duration = .4f;
	float shake_timer = 0;
	Vector2 start_offset{};
	void ShakeScreen(Camera2D &cam);

	Camera2D cam{};
	GameOverlord* game_ol;

	Texture2D game_atlas;
	Texture2D bg_tex;
	Sprite bg_s;

	Button upgrade_btns[ARR_UPGRADE_BTNS]{};

	GameMap map_grid;
	Player player;
	Asteroid asteroids[ARR_ASTEROIDS]{};
	XPOrb xp_orbs[ARR_XP_ORBS]{};
	Bullet bullets[ARR_BULLETS]{};
	Explosion explosions[ARR_EXPLOSIONS]{};
	Cursor cursor;

	bool is_playing_main_menu_text_AED = false;
	bool is_playing_fade_AED = false;
	AEasingData main_text_AED{};
	AEasingData press_play_AED{};
	bool main_menu_space_pressed = false;
	bool game_over_space_pressed = false;
	AEasingData fade_AED{};
};