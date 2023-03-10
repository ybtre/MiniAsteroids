
#include "entities.h"

void SetupBullets(Bullet* bullets, const unsigned int len) {
	if (bullets == nullptr) return;

	for (unsigned int i = 0; i < len; i++) {
		bullets[i].e.is_alive = false;
		bullets[i].lifetime = .5f;
		bullets[i].lifetime_timer = 0.f;

		bullets[i].e.rec = { -100, -100, SPRITE_SIZE_SCALED, SPRITE_SIZE_SCALED };
		bullets[i].e.sprite.src = { 8, 0, SPRITE_SIZE, SPRITE_SIZE };
		bullets[i].e.sprite.dest = {
			bullets[i].e.rec.x + SPRITE_OFFSET,
			bullets[i].e.rec.y + SPRITE_OFFSET,
			bullets[i].e.sprite.src.width * SPRITE_SCALE_MULTI,
			bullets[i].e.sprite.src.height * SPRITE_SCALE_MULTI
		};
		bullets[i].e.sprite.center = {
			(bullets[i].e.sprite.src.width * SPRITE_SCALE_MULTI) / 2,
			(bullets[i].e.sprite.src.height * SPRITE_SCALE_MULTI) / 2
		};

		bullets[i].anim.frames_counter = 0;
		bullets[i].anim.current_frame = 0;
		bullets[i].anim.num_frames = 2;
		bullets[i].anim.is_active = false;

		bullets[i].e.color = C_BULLET;
		bullets[i].e.move_dir = { 0,0 };
		bullets[i].e.speed = 450;
		bullets[i].rotation = 0;
	};
};

void SpawnBullet(Bullet* bullets, const int len, Player& player, const Cursor cursor) {
	for (int i = 0; i < len; i++) {
		if (!bullets[i].e.is_alive) {
			bullets[i].e.is_alive = true;
			bullets[i].lifetime_timer = 0.f;
			bullets[i].anim.is_active = true;
			bullets[i].e.rec.x = player.e.rec.x;
			bullets[i].e.rec.y = player.e.rec.y;
			bullets[i].e.sprite.dest.x = player.e.rec.x + SPRITE_OFFSET;
			bullets[i].e.sprite.dest.y = player.e.rec.y + SPRITE_OFFSET;
			bullets[i].e.move_dir.x = (cursor.s.dest.x - SPRITE_OFFSET) - player.e.rec.x;
			bullets[i].e.move_dir.y = (cursor.s.dest.y - SPRITE_OFFSET) - player.e.rec.y;
			bullets[i].e.move_dir = Vector2Normalize(bullets[i].e.move_dir);
			bullets[i].e.move_dir = Vector2Scale(bullets[i].e.move_dir, bullets[i].e.speed);
			float dx = bullets[i].e.rec.x - (GetMouseX() - SPRITE_OFFSET);
			float dy = bullets[i].e.rec.y - (GetMouseY() - SPRITE_OFFSET);

			bullets[i].rotation = ((atan2(dy, dx)) * 180 / PI) - 90;

			break;
		}
	}
};

void UpdateBullets(Bullet* bullets, const int len) {
	for (int i = 0; i < len; i++) {
		if (bullets[i].e.is_alive) {
			bullets[i].lifetime_timer += GetFrameTime();

			if (bullets[i].lifetime_timer < bullets[i].lifetime) {
				MoveBullet(bullets[i]);
			} else if (bullets[i].lifetime_timer >= bullets[i].lifetime) {
				DestroyBullet(bullets[i]);
			}
		} 
	}
};

void MoveBullet(Bullet& bullet) {
	bullet.e.rec.x += bullet.e.move_dir.x * GetFrameTime();
	bullet.e.sprite.dest.x += bullet.e.move_dir.x * GetFrameTime();

	bullet.e.rec.y += bullet.e.move_dir.y * GetFrameTime();
	bullet.e.sprite.dest.y += bullet.e.move_dir.y * GetFrameTime();

	UpdateAnimation(bullet.anim, true);

	bullet.e.sprite.src.x = (float)(SPRITE_SIZE * bullet.anim.current_frame);
};

void DestroyBullet(Bullet &bullet){
	bullet.e.is_alive = false;
	bullet.anim.is_active = false;
	bullet.e.rec.x = -200;
	bullet.e.rec.y = -200;
}

void RenderBullets(const Bullet* bullets, const int len, const Texture2D& game_atlas) {
	for (int i = 0; i < len; i++) {
		if (bullets[i].e.is_alive) {
#ifdef DEBUGGING
			DrawRectangleLinesEx(bullets[i].e.rec, 1, bullets[i].e.color);
#endif
			DrawTexturePro(game_atlas,
			               bullets[i].e.sprite.src,
			               bullets[i].e.sprite.dest,
			               bullets[i].e.sprite.center,
			               bullets[i].rotation,
			               WHITE);
		}
	}
};

void Upgrade_BulletSpeed(Bullet *bullets, const int len, float multiplier){
	for (int i = 0; i < len; i++) {
		bullets[i].e.speed *= multiplier;
	}
}