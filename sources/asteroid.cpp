#include "entities.h"

void SetupAsteroids(Asteroid* asteroids, size_t len) {
	//assert(asteroids != nullptr);
	if (asteroids == nullptr) return;

	for (unsigned int i = 0; i < len; i++) {
		asteroids[i].e.is_alive = false;

		asteroids[i].e.rec = {
			-100,
			-100,
			SPRITE_SIZE_SCALED, SPRITE_SIZE_SCALED
		};

		asteroids[i].e.sprite.src = { 64, 0, SPRITE_SIZE, SPRITE_SIZE };
		asteroids[i].e.sprite.dest = {
			asteroids[i].e.rec.x + SPRITE_OFFSET,
			asteroids[i].e.rec.y + SPRITE_OFFSET,
			asteroids[i].e.sprite.src.width * SPRITE_SCALE_MULTI,
			asteroids[i].e.sprite.src.height * SPRITE_SCALE_MULTI
		};
		asteroids[i].e.sprite.center = {
			(asteroids[i].e.sprite.src.width * SPRITE_SCALE_MULTI) / 2,
			(asteroids[i].e.sprite.src.height * SPRITE_SCALE_MULTI) / 2
		};

		asteroids[i].e.color = C_ASTEROID;
		asteroids[i].rotation = 0;
		asteroids[i].e.speed = 120;
		asteroids[i].e.move_dir = { 0, 0 };
	}
};

void AsteroidsWaveSpawner(Asteroid *asteroids, const unsigned int len, Player& player, AWave &current_wave){
	assert(asteroids != nullptr);
	
	asteroid_spawn_timer += GetFrameTime();

	if(asteroid_spawn_timer >= current_wave.enemy_spawn_interval){
		for (unsigned int i = 0; i < len; i++) {
			if(!asteroids[i].e.is_alive){
				SpawnAsteroid(asteroids[i], player);
				break;
			}
		}

		asteroid_spawn_timer = 0;
	};
};

void SpawnAsteroid(Asteroid& asteroid, Player &player) {
	asteroid.e.is_alive = false;

	asteroid.e.rec = {
		(float)GetRandomValue(MAP_OFFSET_X, MAP_OFFSET_X + (SPRITE_SIZE_SCALED * MAP_SIZE)),
		(float)GetRandomValue(MAP_OFFSET_Y, MAP_OFFSET_Y + (SPRITE_SIZE_SCALED * MAP_SIZE)),
		SPRITE_SIZE_SCALED, SPRITE_SIZE_SCALED
	};

	while(CheckCollisionCircleRec(
		Vector2{player.e.sprite.dest.x, player.e.sprite.dest.y},
		250,
		asteroid.e.rec
	)){
		asteroid.e.rec = {
			(float)GetRandomValue(MAP_OFFSET_X, MAP_OFFSET_X + (SPRITE_SIZE_SCALED * MAP_SIZE)),
			(float)GetRandomValue(MAP_OFFSET_Y, MAP_OFFSET_Y + (SPRITE_SIZE_SCALED * MAP_SIZE)),
			SPRITE_SIZE_SCALED, SPRITE_SIZE_SCALED
		};
	}

	asteroid.e.sprite.src = { 64, 0, SPRITE_SIZE, SPRITE_SIZE };
	asteroid.e.sprite.dest = {
		asteroid.e.rec.x + SPRITE_OFFSET,
		asteroid.e.rec.y + SPRITE_OFFSET,
		asteroid.e.sprite.src.width * SPRITE_SCALE_MULTI,
		asteroid.e.sprite.src.height * SPRITE_SCALE_MULTI
	};
	asteroid.e.sprite.center = {
		(asteroid.e.sprite.src.width * SPRITE_SCALE_MULTI) / 2,
		(asteroid.e.sprite.src.height * SPRITE_SCALE_MULTI) / 2
	};

	asteroid.e.color = C_ASTEROID;
	asteroid.rotation = 0;
	int random_multi = GetRandomValue(-25, 25);
	while (random_multi == 0) random_multi = GetRandomValue(-1, 1);
	asteroid.e.speed = 120;
	asteroid.e.is_alive = true;
};

void UpdateAsteroids(Asteroid* asteroids, const int len, Player &player) {
	for (int i = 0; i < len; i++) {
		if (asteroids[i].e.is_alive) {
			MoveAsteroid(asteroids[i], player);

			WrapEntityInScreenLimits(asteroids[i].e);
		}
	}
};

void MoveAsteroid(Asteroid& asteroid, Player &player) {
	Vector2 pos = Vector2 { asteroid.e.rec.x, asteroid.e.rec.y };
	Vector2 target = Vector2 { player.e.rec.x, player.e.rec.y };
	pos = Vector2MoveTowards(pos, target, GetFrameTime() * asteroid.e.speed);

	asteroid.e.rec.x = pos.x;
	asteroid.e.sprite.dest.x = asteroid.e.rec.x + SPRITE_OFFSET;
	asteroid.e.rec.y = pos.y;
	asteroid.e.sprite.dest.y = asteroid.e.rec.y + SPRITE_OFFSET;
};

void ResetAsteroids(Asteroid *asteroids, const int len){
	for (int i = 0; i < len; i++) {
		if (asteroids[i].e.is_alive) {
			DestroyAsteroid(asteroids[i]);
		}
	}
}

void DestroyAsteroid(Asteroid &asteroid){
	asteroid.e.is_alive = false;
	asteroid.e.rec.x = -100;
	asteroid.e.rec.y = -100;
};

void RenderAsteroids(const Asteroid* asteroids, const int len, const Texture2D& game_atlas) {
	for (int i = 0; i < len; i++) {
		if (asteroids[i].e.is_alive) {
#ifdef DEBUGGING
#endif
			DrawRectangleLinesEx(asteroids[i].e.rec, 1, asteroids[i].e.color);
			DrawTexturePro(game_atlas,
			               asteroids[i].e.sprite.src,
			               asteroids[i].e.sprite.dest,
			               asteroids[i].e.sprite.center,
			               asteroids[i].rotation,
			               WHITE);
		}
	}
};