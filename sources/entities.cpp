#include "entities.h"

////////////////////
////////////////////
// --- CURSOR --- //
////////////////////
////////////////////
void SetupCursor(Cursor& cursor) {
	HideCursor();

	cursor.s.src = { 104, 0, SPRITE_SIZE, SPRITE_SIZE };
	cursor.s.dest = {
		(float)GetMouseX(), (float)GetMouseY(),
		cursor.s.src.width * SPRITE_SCALE_MULTI,
		cursor.s.src.height * SPRITE_SCALE_MULTI
	};

	cursor.s.center = {
		(cursor.s.src.width * SPRITE_SCALE_MULTI) / 2,
		(cursor.s.src.height * SPRITE_SCALE_MULTI) / 2 };
};

void UpdateCursorPos(Cursor& cursor) {
	cursor.s.dest.x = (float)GetMouseX();
	cursor.s.dest.y = (float)GetMouseY();
};

Vector2 GetCursorPos(Cursor& cursor) {
	return Vector2{ cursor.s.dest.x, cursor.s.dest.y };
}

void RenderCursor(const Cursor& cursor, const Texture2D& game_atlas) {
	DrawTexturePro(
		game_atlas,
		cursor.s.src,
		cursor.s.dest,
		cursor.s.center,
		0,
		WHITE);
};

///////////////////////
///////////////////////
// --- XP orbss --- //
///////////////////////
///////////////////////
void SetupXPOrbs(XPOrb *orbs){
	assert(orbs != nullptr);

	for (int i = 0; i < ARR_XP_ORBS; i++) {
		orbs[i].is_acitve = false;
		orbs[i].pick_radius = 10;
		orbs[i].pos = { -300, -300 };
		orbs[i].s.src = { 96, 16, SPRITE_SIZE, SPRITE_SIZE };
		orbs[i].s.dest = {
			orbs[i].pos.x,
			orbs[i].pos.y,
			orbs[i].s.src.width * 4,
			orbs[i].s.src.height * 4
		};
		orbs[i].s.center = {
			(orbs[i].s.src.width * 4) / 2,
			(orbs[i].s.src.height * 4) / 2
		};
	};
};

XPOrb& GetInactiveOrb(XPOrb *orbs){
	assert(orbs != nullptr);

	for (int i = 0; i < ARR_XP_ORBS; i++) {
		if(!orbs[i].is_acitve){
			return orbs[i];
		};
	};
};

void SpawnXPOrb(XPOrb &orb, Asteroid &asteroid){
	orb.is_acitve = true;
	orb.pos = Vector2{asteroid.e.sprite.dest.x, asteroid.e.sprite.dest.y};
	orb.s.dest.x = orb.pos.x;
	orb.s.dest.y = orb.pos.y;
}

void UpdateXPOrbs(XPOrb *orbs, Player &player){
	assert(orbs != nullptr);

	for(int i = 0; i < ARR_XP_ORBS; i++){
		if(!orbs[i].is_acitve) continue;

		if(CheckCollisionCircles(
			orbs[i].pos, orbs[i].pick_radius,
			Vector2{player.e.sprite.dest.x, player.e.sprite.dest.y}, 
			player.stats.xp_pickup_range))
			{
				orbs[i].is_acitve = false;
				player.stats.current_xp++;
			}
	}
}

void RenderXPOrbs(const XPOrb* orbs, Texture2D &game_atlas){
	assert(orbs != nullptr);

	for(int i = 0; i < ARR_XP_ORBS; i++){
		if(orbs[i].is_acitve){
		DrawTexturePro(
			game_atlas,
			orbs[i].s.src,
			orbs[i].s.dest,
			orbs[i].s.center,
			0,
			WHITE
		);
		// DrawCircleLines(orbs[i].s.dest.x, orbs[i].s.dest.y, orbs[i].pick_radius, GREEN);
		// DrawCircleLines(orbs[i].pos.x, orbs[i].pos.y, 10, RED);
		}
	}
};

///////////////////////
///////////////////////
// --- MISC --- //
///////////////////////
///////////////////////
void WrapEntityInScreenLimits(Entity& e) {
	int grid_dlen = 13 * SPRITE_SIZE_SCALED;
	if (e.rec.y <= MAP_OFFSET_Y - SPRITE_OFFSET) {
		e.rec.y = (float)(MAP_OFFSET_Y + grid_dlen - SPRITE_OFFSET);
		e.sprite.dest.y = (float)(MAP_OFFSET_Y + grid_dlen);
	}
	else if (e.rec.y >= ((MAP_OFFSET_Y - SPRITE_OFFSET) + grid_dlen)) {
		e.rec.y = MAP_OFFSET_Y - SPRITE_OFFSET;
		e.sprite.dest.y = MAP_OFFSET_Y;
	}
	else if (e.rec.x <= MAP_OFFSET_X - SPRITE_OFFSET) {
		e.rec.x = (float)(MAP_OFFSET_X + grid_dlen - SPRITE_OFFSET);
		e.sprite.dest.x = (float)(MAP_OFFSET_X + grid_dlen);
	}
	else if (e.rec.x >= ((MAP_OFFSET_X - SPRITE_OFFSET) + grid_dlen)) {
		e.rec.x = MAP_OFFSET_X - SPRITE_OFFSET;
		e.sprite.dest.x = MAP_OFFSET_X;
	}
};

void UpdateAnimation(AnimData& anim, bool should_loop) {
	if (anim.is_active) {
		anim.frames_counter++;

		if (anim.frames_counter > 2) {
			anim.current_frame++;

			if (anim.current_frame >= anim.num_frames) {
				anim.current_frame = 0;

				if (!should_loop) anim.is_active = false;
			}
			anim.frames_counter = 0;
		}
	}
};

void InitUpgradeButtons(Button* upgrade_btns, const int len) {
	assert(upgrade_btns != nullptr);
	assert(len == 3);

	for (int i = 0; i < len; i++) {
		upgrade_btns[i].is_highlighted = false;
		upgrade_btns[i].is_pressed = false;

		upgrade_btns[i].rec = {
			((GLOBALS::SCREEN.x * ((i + 1) * .25f)) - BUTTON_SPRITE_OFFSET),
			GLOBALS::SCREEN.y / 2 - BUTTON_SPRITE_OFFSET,
			BUTTON_SPRITE_SIZE * SPRITE_SCALE_MULTI,
			BUTTON_SPRITE_SIZE * SPRITE_SCALE_MULTI
		};

		upgrade_btns[i].s.src = { 0, 32, BUTTON_SPRITE_SIZE, BUTTON_SPRITE_SIZE };
		upgrade_btns[i].s.dest = {
			upgrade_btns[i].rec.x + BUTTON_SPRITE_OFFSET,
			upgrade_btns[i].rec.y + BUTTON_SPRITE_OFFSET,
			upgrade_btns[i].s.src.width * SPRITE_SCALE_MULTI,
			upgrade_btns[i].s.src.height * SPRITE_SCALE_MULTI
		};
		upgrade_btns[i].s.center = {
			(upgrade_btns[i].s.src.width * SPRITE_SCALE_MULTI) / 2,
			(upgrade_btns[i].s.src.height * SPRITE_SCALE_MULTI) / 2
		};
	}
}

void RandomizeUpgradeButtons(Button* upgrade_btns, const int len) {
	assert(upgrade_btns != nullptr);
	assert(len == 3);

	for (int i = 0; i < len; i++) {
		int r = GetRandomValue(0, 2);
		switch (r) {
		case 0:
			upgrade_btns[i].upgrade = FIRE_RATE;
			break;
		case 1:
			upgrade_btns[i].upgrade = PLAYER_SPEED;
			break;
		case 2:
			upgrade_btns[i].upgrade = BULLET_SPEED;
			break;
		default:
			break;
		}
	}
};