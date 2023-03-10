#include "engine.h"

void Engine::Init() {
	game_ol = new GameOverlord();

	game_ol->SetupGame();

	bg_tex = LoadTexture("../assets/background.png");
	bg_s.src = { 0, 0, 420, 315 };
	bg_s.dest = { 0, 0, bg_s.src.width * 2.44f, bg_s.src.height * 2.44f };
	bg_s.center = { 0,0 };

	InitUpgradeButtons(upgrade_btns, ARR_UPGRADE_BTNS);

	game_atlas = LoadTexture("../assets/game_atlas_8x8.png");

	SetupGameMap(map_grid);

	SetupPlayer(player);

	cam.target = Vector2{ player.e.sprite.dest.x - SPRITE_OFFSET, player.e.sprite.dest.y - SPRITE_OFFSET };
	cam.offset = Vector2{ GLOBALS::SCREEN.x / 2, GLOBALS::SCREEN.y / 2 };
	start_offset = cam.offset;
	cam.rotation = 0.f;
	cam.zoom = 1.f;

	SetupAsteroids(asteroids, ARR_ASTEROIDS);

	SetupBullets(bullets, ARR_BULLETS);

	SetupCursor(cursor);

	SetupExplosions(explosions, ARR_EXPLOSIONS);

	SetupXPOrbs(xp_orbs);

	main_text_AED.counter = 0;
	main_text_AED.duration = 90;
	main_text_AED.start = { GLOBALS::SCREEN.x / 2 - 240, GLOBALS::SCREEN.y / 2 - 50 };
	main_text_AED.end = { GLOBALS::SCREEN.x / 2 - 175, -600 };
	main_text_AED.current = { main_text_AED.start.x, main_text_AED.start.y };

	press_play_AED.counter = 0;
	press_play_AED.duration = 90;
	press_play_AED.start = { GLOBALS::SCREEN.x / 2 - 365, GLOBALS::SCREEN.y / 2 + 40 };
	press_play_AED.end = { GLOBALS::SCREEN.x / 2 - 250,  GLOBALS::SCREEN.y + 100 };
	press_play_AED.current = { press_play_AED.start.x, press_play_AED.start.y };

	fade_AED.counter = 0;
	fade_AED.duration = 90;
	fade_AED.start = { 0, 0 };
	fade_AED.end = { 800, 800 };
	fade_AED.current = fade_AED.start;
};

void Engine::Shutdown() const
{
	UnloadTexture(game_atlas);
	UnloadTexture(bg_tex);
	delete(game_ol);
};

void Engine::Update() {
	switch (game_ol->GetCurrentScreen()) {
	case 0:
		UpdateMainMenu();
		break;
	case 1:
		UpdateGameplay();
		break;
	case 2:
		UpdateGameOver();
		break;
	case 3:
		UpdateUpgradeScreen();
		break;
	}
};

void Engine::Render() {
	BeginDrawing();
	ClearBackground(BLACK);
	{
		//------Text Render------//
		DrawFPS(0, 0);

		switch (game_ol->GetCurrentScreen()) {
		case 0:
			RenderMainMenu();
			break;
		case 1:
			RenderGameplay();
			break;
		case 2:
			RenderGameOver();
			break;
		case 3:
			RenderUpgradeScreen();
			break;
		}

		if (is_playing_fade_AED) {
			RenderFadeTransition();
		}

#ifdef DEBUGGING
		DrawLine(GLOBALS::SCREEN.x / 2, 0, GLOBALS::SCREEN.x / 2, GLOBALS::SCREEN.y, RED);
		DrawLine(0, GLOBALS::SCREEN.y / 2, GLOBALS::SCREEN.x, GLOBALS::SCREEN.y / 2, RED);
#endif
	}
	EndDrawing();
};

void Engine::RenderFadeTransition() {
	fade_AED.counter++;

	fade_AED.current.x = EaseQuadInOut((float)fade_AED.counter, fade_AED.start.x, fade_AED.end.x, (float)fade_AED.duration / 2);

	DrawCircle((int)GLOBALS::SCREEN.x / 2, (int)GLOBALS::SCREEN.y / 2, (float)fade_AED.current.x, C_BG);

	if (fade_AED.counter >= fade_AED.duration) {
		fade_AED.counter = 0;
		is_playing_fade_AED = false;
		if (game_ol->GetCurrentScreen() == 1) {
			game_ol->is_wave_starting = true;
		}
	}
}

//-----------------------//
//------ MAIN MENU ------//
//-----------------------//
void Engine::SetMainMenu() {
	main_text_AED.counter = 0;
	main_text_AED.duration = 90;
	main_text_AED.start = { GLOBALS::SCREEN.x / 2 - 240, GLOBALS::SCREEN.y / 2 - 50 };
	main_text_AED.end = { GLOBALS::SCREEN.x / 2 - 175, -600 };
	main_text_AED.current = { main_text_AED.start.x, main_text_AED.start.y };

	press_play_AED.counter = 0;
	press_play_AED.duration = 90;
	press_play_AED.start = { GLOBALS::SCREEN.x / 2 - 365, GLOBALS::SCREEN.y / 2 + 40 };
	press_play_AED.end = { GLOBALS::SCREEN.x / 2 - 250,  GLOBALS::SCREEN.y + 100 };
	press_play_AED.current = { press_play_AED.start.x, press_play_AED.start.y };
}

void Engine::UpdateMainMenu() {
	UpdateCursorPos(cursor);

	if (IsKeyPressed(KEY_SPACE)) {
		main_menu_space_pressed = true;
		is_playing_main_menu_text_AED = true;
	}

	if (is_playing_main_menu_text_AED) {
		main_text_AED.counter++;
		press_play_AED.counter++;

		main_text_AED.current.y = EaseBounceIn((float)main_text_AED.counter, main_text_AED.start.y, main_text_AED.end.y, (float)main_text_AED.duration);

		press_play_AED.current.y = EaseBounceIn((float)press_play_AED.counter, press_play_AED.start.y, press_play_AED.end.y, (float)press_play_AED.duration);

		if (main_text_AED.counter >= main_text_AED.duration - 30) {
			is_playing_fade_AED = true;
		}

		if (main_text_AED.counter >= main_text_AED.duration) {
			is_playing_main_menu_text_AED = false;
			main_text_AED.counter = 0;

			press_play_AED.counter = 0;
		}
	}

	if (main_menu_space_pressed && fade_AED.counter >= fade_AED.duration / 2) {
		main_menu_space_pressed = false;
		game_ol->SetCurrentScreen(game_ol->GAMEPLAY);
	}
};

void Engine::RenderMainMenu() {
	DrawTexturePro(bg_tex, bg_s.src, bg_s.dest, bg_s.center, 0, WHITE);

	DrawText("ASTEROIDS", (int)main_text_AED.start.x, (int)main_text_AED.current.y, 80, C_TEXT);

	DrawText("PRESS SPACE TO PLAY", (int)press_play_AED.start.x, (int)press_play_AED.current.y, 60, C_TEXT);

	RenderCursor(cursor, game_atlas);
};

//----------------------//
//------ GAMEPLAY ------//
//----------------------//
void Engine::UpdateGameplay() {
	UpdateCursorPos(cursor);

	if (is_playing_fade_AED) return;

	if (IsKeyPressed(KEY_P)) game_ol->is_paused = !game_ol->is_paused;
	if (!game_ol->is_paused)
	{
		game_ol->gameplay_time_total += GetFrameTime();

		if (game_ol->is_wave_starting) {
			if (game_ol->current_wave >= ARR_WAVES) {
				SetMainMenu();
				game_ol->SetCurrentScreen(game_ol->MAIN_MENU);
				return;
			}
			game_ol->wave_duration = game_ol->waves[game_ol->current_wave].duration;

			game_ol->is_wave_starting = false;
		}

		if(player.stats.current_xp >= player.stats.required_xp){
			player.stats.current_xp = 0;
			IncreaseReqXP(player);

			RandomizeUpgradeButtons(upgrade_btns, ARR_UPGRADE_BTNS);
			game_ol->SetCurrentScreen(game_ol->UPGRADE);
		}
		
		game_ol->wave_duration -= GetFrameTime();
		if (game_ol->wave_duration < 0) {
			game_ol->current_wave++;
			game_ol->is_wave_starting = true;
		}

		AsteroidsWaveSpawner(asteroids, ARR_ASTEROIDS, player, game_ol->waves[game_ol->current_wave]);

		if (is_shaking) shake_timer += GetFrameTime();
		if (is_shaking && shake_timer <= shake_duration) {
			ShakeScreen(cam);
		}
		else {
			is_shaking = false;
			shake_timer = 0;
		}

		WrapEntityInScreenLimits(player.e);

		UpdatePlayer(player);

		UpdateAsteroids(asteroids, ARR_ASTEROIDS, player);

		if (IsMouseButtonDown(0) && player.stats.fire_rate_timer <= 0) {
			player.stats.fire_rate_timer = player.stats.fire_rate;

			SpawnBullet(bullets, ARR_BULLETS, player, cursor);
		}

		UpdateExplosions(explosions, ARR_EXPLOSIONS);

		UpdateBullets(bullets, ARR_BULLETS);

		UpdateXPOrbs(xp_orbs, player);

		//------Collision Detection------//
		for (auto& asteroid : asteroids) {
			if (!asteroid.e.is_alive) continue;
			for (auto& bullet : bullets) {
				if (!bullet.e.is_alive) continue;
				if (CheckCollisionRecs(bullet.e.rec, asteroid.e.rec)) {
					game_ol->score += 1;
					XPOrb& o = GetInactiveOrb(xp_orbs);
					SpawnXPOrb(o, asteroid);
					DestroyBullet(bullet);
					DestroyAsteroid(asteroid);
					//asteroid.e.is_alive = false;
					StartExplosion(explosions, ARR_EXPLOSIONS, Vector2{ asteroid.e.sprite.dest.x, asteroid.e.sprite.dest.y });
				}
			}

			if (CheckCollisionRecs(player.e.rec, asteroid.e.rec)) {
				DestroyAsteroid(asteroid);
				player.stats.lives--;
				StartExplosion(explosions, ARR_EXPLOSIONS, Vector2{ player.e.sprite.dest.x, player.e.sprite.dest.y });
				is_shaking = true;

				if (player.stats.lives > 0) {
					ResetPlayer_OnDie(player);
				}
				else if (player.stats.lives <= 0) {
					player.e.is_alive = false;
				}
			}
		}

#ifdef DEBUGGING
		auto p_size = sizeof(player);
		auto ent_size = sizeof(player.e);
		auto a_size = sizeof(asteroids[0]);
		auto aa_size = sizeof(asteroids);
		auto b_size = sizeof(bullets[0]);
		auto bb_size = sizeof(bullets);
		auto e_size = sizeof(explosions[0]);
		auto ee_size = sizeof(explosions);
		auto m_size = sizeof(map_grid);
#endif
	}
	else {
		game_ol->pause_blink_counter++;
	}
};

void Engine::RenderGameplay() {
	BeginMode2D(cam);
	{
		if (!player.e.is_alive) {
			game_ol->SetCurrentScreen(game_ol->GAME_OVER);
		}
		else {
			//------Objects Render------//
			DrawTexturePro(bg_tex, bg_s.src, bg_s.dest, bg_s.center, 0, WHITE);

			RenderGameMap(map_grid, game_atlas);

			RenderXPOrbs(xp_orbs, game_atlas);

			RenderAsteroids(asteroids, ARR_ASTEROIDS, game_atlas);

			RenderBullets(bullets, ARR_BULLETS, game_atlas);

			RenderExplosions(explosions, ARR_EXPLOSIONS, game_atlas);

			RenderPlayer(player, game_atlas);

			RenderCursor(cursor, game_atlas);

#ifdef DEBUGGING
			DrawCircleLines(player.e.sprite.dest.x, player.e.sprite.dest.y, 125, RED);
#endif
		}
	};
	EndMode2D();

	//------HUD Render------//
	for (int i = 0; i < player.stats.lives; i++) {
		game_ol->live_dest.x = (float)(i * SPRITE_SIZE_SCALED);
		game_ol->live_dest.x += 10;
		DrawTexturePro(
			game_atlas,
			game_ol->live_src,
			game_ol->live_dest,
			Vector2{ 0, 0 },
			0,
			WHITE);
	}

	DrawTexturePro(
		game_atlas,
		game_ol->score_src,
		game_ol->score_dest,
		Vector2{ 0, 0 },
		0,
		WHITE);
	DrawText(TextFormat("%d", game_ol->score), 65, 100, 50, RAYWHITE);
	DrawText(TextFormat("%d", player.stats.current_xp), 65, 150, 50, RAYWHITE);
	DrawText(TextFormat("%d", player.stats.total_xp), 65, 200, 50, RAYWHITE);
	DrawText(TextFormat("%.1f", player.stats.required_xp), 65, 250, 50, RAYWHITE);

	DrawText(TextFormat("Wave %d", (int)game_ol->current_wave + 1), (int)(GLOBALS::SCREEN.x / 2 - 30), 10, 30, RAYWHITE);
	DrawText(TextFormat("%d", static_cast<int>(game_ol->wave_duration)), (int)(GLOBALS::SCREEN.x / 2), 40, 50, RAYWHITE);

	if (game_ol->is_paused && ((game_ol->pause_blink_counter / 30) % 2 == 0)) {
		DrawText("GAME PAUSED", (int)GLOBALS::SCREEN.x / 2 - 290, (int)GLOBALS::SCREEN.y / 2 - 50, 80, RED);
	}
	//#ifdef DEBUGGING

	//#endif

	DrawFPS(0, 0);
};

//----------------------//
//------ UPGRADE  ------//
//----------------------//

void Engine::UpdateUpgradeScreen() {
	UpdateCursorPos(cursor);

	for (auto& b : upgrade_btns) {
		if (CheckCollisionPointRec(GetCursorPos(cursor), b.rec)) {
			b.is_highlighted = true;

			if (IsMouseButtonPressed(0)) {
				b.is_pressed = true;
			}
			else {
				b.is_pressed = false;
			}
		}
		else {
			b.is_highlighted = false;
		}
	}

	for (auto& b : upgrade_btns) {
		if (b.is_pressed) {
			b.is_pressed = false;

			if(b.upgrade == FIRE_RATE){
				Upgrade_PlayerFirerate(player, 1.2f);
			} else if(b.upgrade == PLAYER_SPEED){
				Upgrade_PlayerSpeed(player, 1.2f);
			} else if(b.upgrade == BULLET_SPEED){
				Upgrade_BulletSpeed(bullets, ARR_BULLETS, 1.2f);
			}

			game_ol->SetCurrentScreen(game_ol->GAMEPLAY);
		}
	}
};

void Engine::RenderUpgradeScreen() {
	DrawTexturePro(bg_tex, bg_s.src, bg_s.dest, bg_s.center, 0, WHITE);

	for (auto& b : upgrade_btns) {
		if (b.is_highlighted) {
			if (b.is_pressed) {
				DrawTexturePro(game_atlas, b.s.src, b.s.dest, b.s.center, 0, DARKBLUE);
			}
			else {
				DrawTexturePro(game_atlas, b.s.src, b.s.dest, b.s.center, 0, C_BTN_HOVER);
			}
		}
		else {
			DrawTexturePro(game_atlas, b.s.src, b.s.dest, b.s.center, 0, WHITE);
		};

		
		if(b.upgrade == FIRE_RATE){
			DrawText("+FIRE RATE", b.s.dest.x - 80, b.s.dest.y - 10, 20, RAYWHITE);
		} else if(b.upgrade == PLAYER_SPEED){
			DrawText("+SHIP SPEED", b.s.dest.x - 80, b.s.dest.y - 10, 20, RAYWHITE);
		} else if(b.upgrade == BULLET_SPEED){
			DrawText("+BULLET SPEED", b.s.dest.x - 80, b.s.dest.y - 10, 20, RAYWHITE);
		}
		//DrawText("SPEED++", b.s.dest.x - 60, b.s.dest.y - 10, 20, RAYWHITE);

#ifdef DEBUGGING
		//DrawRectangleLinesEx(b.rec, 3, GREEN);
#endif
	}

	DrawText("SELECT UPGRADE", GLOBALS::SCREEN.x / 2 - 175, GLOBALS::SCREEN.y * .75f, 40, C_TEXT);
	DrawText("TO CONTINUE", GLOBALS::SCREEN.x / 2 - 135, GLOBALS::SCREEN.y * .8f, 40, C_TEXT);

	RenderCursor(cursor, game_atlas);
#ifdef DEBUGGING
	//DrawCircleLines(cursor.s.dest.x, cursor.s.dest.y, 10, GREEN);
#endif
	}

//-----------------------//
//------ GAME OVER ------//
//-----------------------//
void Engine::UpdateGameOver() {
	UpdateCursorPos(cursor);

	main_text_AED.current = { main_text_AED.start.x, main_text_AED.start.y };
	press_play_AED.current = { press_play_AED.start.x, press_play_AED.start.y };
	fade_AED.current = fade_AED.start;

	ResetPlayer_OnGameOver(player);
	game_ol->ResetGame();

	if (IsKeyPressed(KEY_SPACE)) {
		game_over_space_pressed = true;
		is_playing_fade_AED = true;
	}

	if (game_over_space_pressed && fade_AED.counter >= fade_AED.duration / 2) {
		game_over_space_pressed = false;

		SetMainMenu();
		game_ol->SetCurrentScreen(game_ol->MAIN_MENU);
	}
};
void Engine::RenderGameOver() {
	DrawTexturePro(bg_tex, bg_s.src, bg_s.dest, bg_s.center, 0, WHITE);

	string game_over = "GAME OVER";
	DrawText(game_over.c_str(), (int)main_text_AED.start.x, (int)main_text_AED.current.y, 80, C_TEXT);
	DrawText("PRESS SPACE TO PLAY", (int)press_play_AED.start.x, (int)press_play_AED.current.y, 60, C_TEXT);

	RenderCursor(cursor, game_atlas);
};

void Engine::ShakeScreen(Camera2D& cam) {
	if (is_shaking) {
		cam.offset = Vector2{ sinf(float(GetTime() * 90)) * 3, sinf(float(GetTime() * 180)) * 3 };
		cam.offset.x += start_offset.x;
		cam.offset.y += start_offset.y;
	}
	else {
		cam.offset = start_offset;
	}
};