#include "entities.h"


void StartExplosion(Explosion* e, const int len, const Vector2 spawn_at) {
	for (int i = 0; i < len; i++) {
		if (!e[i].anim.is_active) {
			e[i].s.dest = { spawn_at.x, spawn_at.y, e[i].s.src.width * SPRITE_SCALE_MULTI, e[i].s.src.height * SPRITE_SCALE_MULTI };

			e[i].anim.is_active = true;

			break;
		}
	}
};

void SetupExplosions(Explosion* e, const int len) {
	assert(e != nullptr);

	for (int i = 0; i < len; i++) {
		e[i].anim.frames_counter = 0;
		e[i].anim.current_frame = 0;
		e[i].anim.num_frames = 6;
		e[i].s.src = { 0, 16, SPRITE_SIZE * 2, SPRITE_SIZE * 2 };
		e[i].s.dest = { -100, -100, e[i].s.src.width * SPRITE_SCALE_MULTI, e[i].s.src.height * SPRITE_SCALE_MULTI };
		e[i].s.center = { (e[i].s.src.height * SPRITE_SCALE_MULTI) / 2, (e[i].s.src.height * SPRITE_SCALE_MULTI) / 2 };

		e[i].anim.is_active = false;
	};
};

void UpdateExplosions(Explosion* e, const int len) {
	assert(e != nullptr);

	for (int i = 0; i < len; i++) {
		UpdateAnimation(e[i].anim, false);
		e[i].s.src.x = (float)(16 * e[i].anim.current_frame);
	}
};

void RenderExplosions(Explosion* e, const int len, const Texture2D& game_atlas) {
	assert(e != nullptr);

	for (int i = 0; i < len; i++) {
		if (e[i].anim.is_active) {
			DrawTexturePro(game_atlas,
			               e[i].s.src,
			               e[i].s.dest,
			               e[i].s.center,
			               (float)GetRandomValue(0, 270),
			               WHITE);
		}
	}
};