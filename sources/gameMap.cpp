#include "entities.h"

void SetupGameMap(GameMap& map) {
	map.s.src = { 40, 0, SPRITE_SIZE, SPRITE_SIZE };
	//int x
	map.s.dest = { MAP_OFFSET_X, MAP_OFFSET_Y, map.s.src.width * SPRITE_SCALE_MULTI, map.s.src.height * SPRITE_SCALE_MULTI };
	map.s.center = { map.s.src.width * SPRITE_SCALE_MULTI / 2, map.s.src.height * SPRITE_SCALE_MULTI / 2 };
}

void RenderGameMap(GameMap& map, const Texture2D& game_atlas) {
	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++) {
			map.s.dest.x = (float)(x * SPRITE_SIZE_SCALED);
			map.s.dest.y = (float)(y * SPRITE_SIZE_SCALED);
			map.s.dest.x += MAP_OFFSET_X;
			map.s.dest.y += MAP_OFFSET_Y;

			DrawTexturePro(game_atlas,
			               map.s.src,
			               map.s.dest,
			               map.s.center,
			               0,
			               WHITE);
		}
	}
}
