#pragma once

#include "globals.h"
#include "gameoverlord.h"
#include <cassert>

	//--- Data --- //
	typedef struct Sprite{
		Rectangle src;
		Rectangle dest;
		Vector2 center;
	} Sprite;

	typedef struct Entity{
		bool is_alive;
		Rectangle rec;
		Sprite sprite;
		
		Color color;
		float speed;
		Vector2 move_dir;
	} Entity;

	typedef struct AnimData{
		bool is_active;
		int frames_counter;
		int current_frame;
		int num_frames;
	} AnimData;

	typedef struct PlayerStats {
		int lives;
		float fire_rate;
		float fire_rate_timer;
	} PlayerStats;

	enum UPGRADES {
		FIRE_RATE		= 0,
		PLAYER_SPEED 	= 1,
		BULLET_SPEED 	= 2
	};

	typedef struct Button {
		Rectangle rec;
		Sprite s;
		bool is_highlighted;
		bool is_pressed;
		int upgrade;
	} Button;

	typedef struct Cursor {
		Sprite s;
	} Cursor;

	typedef struct Player {
		Entity e;
		Sprite engine_s;
		AnimData engine_anim;
		PlayerStats stats;
		float rotation;
	} Player;

	typedef struct Asteroid {
		Entity e;
		float rotation;
	} Asteroid;

	typedef struct GameMap {
		Sprite s;
	} GameMap;

	typedef struct Bullet {
		Entity e;
		AnimData anim;
		float rotation;
		float lifetime;
		float lifetime_timer;
	} Bullet;

	typedef struct Explosion{
		Sprite s;
		AnimData anim;
	} Explosion;

	// --- Game Map--- //
	void SetupGameMap(GameMap &map);
	void RenderGameMap(GameMap &map, const Texture2D &game_atlas);

	// -- Player --- //
	void SetupPlayer(Player &player);
	void ResetPlayer_OnDie(Player &player);
	void ResetPlayer_OnGameOver(Player &player);

	void UpdatePlayer(Player &player);
	void RenderPlayer(const Player &player, const Texture2D& game_atlas);

	void Upgrade_PlayerFirerate(Player &player, float multiplier);
	void Upgrade_PlayerSpeed(Player &player, float multiplier);

	// --- Bullet --- //
	void SetupBullets(Bullet *bullets, unsigned int len);
	void SpawnBullet(Bullet *bullets, const int len, Player &player, const Cursor cursor);

	void UpdateBullets(Bullet *bullets, int len);
	void MoveBullet(Bullet &bullet);
	void DestroyBullet(Bullet &bullet);

	void RenderBullets(const Bullet *bullets, int len, const Texture2D &game_atlas);

	void Upgrade_BulletSpeed(Bullet *bullets, const int len, float multiplier);

	// --- Asteroid--- //
	void SetupAsteroids(Asteroid* asteroids, size_t len);
	void AsteroidsWaveSpawner(Asteroid *asteroids, const unsigned int len, Player& player, AWave &current_wave);
	static float asteroid_spawn_timer = 0;

	void SpawnAsteroid(Asteroid &asteroid, Player &player);

	void UpdateAsteroids(Asteroid *asteroids, int len, Player &player);
	void MoveAsteroid(Asteroid& asteroid, Player &player);

	void ResetAsteroids(Asteroid *asteroids, const int len);
	void DestroyAsteroid(Asteroid &asteroid);

	void RenderAsteroids(const Asteroid *asteroids, int len, const Texture2D &game_atlas);

	// --- Explosion--- //
	void SetupExplosions(Explosion *e, const int len);
	void StartExplosion(Explosion *e, const int len, const Vector2 spawn_at);

	void UpdateExplosions(Explosion *e, const int len);
	void RenderExplosions(Explosion *e, const int len, const Texture2D &game_atlas);

	// --- Cursor --- //
	void SetupCursor(Cursor &cursor);
	void UpdateCursorPos(Cursor &cursor);
	Vector2 GetCursorPos(Cursor &cursor);
	void RenderCursor(const Cursor &cursor, const Texture2D &game_atlas);

	// --- MISC --- //
	void WrapEntityInScreenLimits(Entity &entity);
	void UpdateAnimation(AnimData &anim, bool should_loop);

	void InitUpgradeButtons(Button *upgrade_btns, const int len);
	void RandomizeUpgradeButtons(Button *upgrade_btns, const int len);