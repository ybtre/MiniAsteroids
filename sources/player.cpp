#include "entities.h"

void SetupPlayer(Player& player) {
	player.e.is_alive = true;
	player.stats.lives = 3;
	player.stats.fire_rate = .4f;
	player.stats.fire_rate_timer = 0;
	player.stats.xp_pickup_range = 50;
	player.rotation = 0;

	player.e.rec = { (GLOBALS::SCREEN.x / 2), (GLOBALS::SCREEN.y / 2), SPRITE_SIZE_SCALED, SPRITE_SIZE_SCALED };
	player.e.sprite.src = { 56, 0, SPRITE_SIZE, SPRITE_SIZE };
	player.e.sprite.dest = {
		player.e.rec.x + SPRITE_OFFSET,
		player.e.rec.y + SPRITE_OFFSET,
		player.e.sprite.src.width * SPRITE_SCALE_MULTI,
		player.e.sprite.src.height * SPRITE_SCALE_MULTI
	};
	player.e.sprite.center = {
		(player.e.sprite.src.width * SPRITE_SCALE_MULTI) / 2,
		(player.e.sprite.src.height * SPRITE_SCALE_MULTI) / 2
	};

	player.engine_s.src = { 72, 0, SPRITE_SIZE, SPRITE_SIZE * 2 };
	player.engine_s.dest = {
		player.e.sprite.dest.x,
		player.e.sprite.dest.y,
		player.e.sprite.dest.width,
		player.e.sprite.dest.height * 2
	};
	player.engine_s.center = {
		player.e.sprite.center.x,
		player.e.sprite.center.y
	};

	player.engine_anim.frames_counter = 0;
	player.engine_anim.current_frame = 0;
	player.engine_anim.num_frames = 4;
	player.engine_anim.is_active = false;

	player.e.color = C_PLAYER;
	player.e.speed = 110;
};

void ResetPlayer_OnDie(Player& player) {
	player.e.rec = { GLOBALS::SCREEN.x / 2, GLOBALS::SCREEN.y / 2, SPRITE_SIZE_SCALED, SPRITE_SIZE_SCALED };
	player.e.sprite.dest = {
		player.e.rec.x + SPRITE_OFFSET,
		player.e.rec.y + SPRITE_OFFSET,
		player.e.sprite.src.width * SPRITE_SCALE_MULTI,
		player.e.sprite.src.height * SPRITE_SCALE_MULTI
	};
	player.engine_s.dest = {
		player.e.sprite.dest.x,
		player.e.sprite.dest.y,
		player.e.sprite.dest.width,
		player.e.sprite.dest.height * 2
	};
};

void ResetPlayer_OnGameOver(Player& player) {
	player.e.is_alive = true;
	player.stats.lives = 3;
	player.e.rec = { GLOBALS::SCREEN.x / 2, GLOBALS::SCREEN.y / 2, SPRITE_SIZE_SCALED, SPRITE_SIZE_SCALED };
	player.e.sprite.dest = {
		player.e.rec.x + SPRITE_OFFSET,
		player.e.rec.y + SPRITE_OFFSET,
		player.e.sprite.src.width * SPRITE_SCALE_MULTI,
		player.e.sprite.src.height * SPRITE_SCALE_MULTI
	};
	player.engine_s.dest = {
		player.e.sprite.dest.x,
		player.e.sprite.dest.y,
		player.e.sprite.dest.width,
		player.e.sprite.dest.height * 2
	};
};

void UpdatePlayer(Player& player) {

	player.stats.fire_rate_timer -= GetFrameTime();

	//------Player movement------//
	player.engine_anim.is_active = true;
	if (IsKeyDown(KEY_W)) {
		player.e.rec.y -= player.e.speed * GetFrameTime();
		player.e.sprite.dest.y -= player.e.speed * GetFrameTime();
	}
	if (IsKeyDown(KEY_S)) {
		player.e.rec.y += player.e.speed* GetFrameTime();
		player.e.sprite.dest.y += player.e.speed* GetFrameTime();
	}
	if (IsKeyDown(KEY_A)) {
		player.e.rec.x -= player.e.speed* GetFrameTime();
		player.e.sprite.dest.x -= player.e.speed* GetFrameTime();
	}
	if (IsKeyDown(KEY_D)) {
		player.e.rec.x += player.e.speed* GetFrameTime();
		player.e.sprite.dest.x += player.e.speed* GetFrameTime();
	}

	float dx = player.e.rec.x - (GetMouseX() - SPRITE_OFFSET);
	float dy = player.e.rec.y - (GetMouseY() - SPRITE_OFFSET);
	float final_rotation = ((atan2(dy, dx)) * 180 / PI) - 90;

	player.rotation = final_rotation;

	player.engine_s.dest.x = player.e.sprite.dest.x;
	player.engine_s.dest.y = player.e.sprite.dest.y;
	UpdateAnimation(player.engine_anim, true);
	player.engine_s.src.x = (float)(72 + (SPRITE_SIZE * player.engine_anim.current_frame));
};

void RenderPlayer(const Player& player, const Texture2D& game_atlas) {
#ifdef DEBUGGING
	DrawRectangleLinesEx(player.e.rec, 1, player.e.color);
	DrawCircleLines(player.e.rec.x, player.e.rec.y, 10, player.e.color);
#endif
	if (player.engine_anim.is_active) {
		DrawTexturePro(game_atlas,
		               player.engine_s.src,
		               player.engine_s.dest,
		               player.engine_s.center,
		               player.rotation,
		               WHITE);
	}

	DrawTexturePro(game_atlas,
	               player.e.sprite.src,
	               player.e.sprite.dest,
	               player.e.sprite.center,
	               player.rotation,
	               WHITE);
};

void Upgrade_PlayerFirerate(Player &player, float multiplier){
	player.stats.fire_rate /= multiplier;
}

void Upgrade_PlayerSpeed(Player &player, float multiplier){
	player.e.speed *= multiplier;
}