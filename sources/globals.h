#pragma once

#include <iostream>
#include <string>

#include "raylib.h"
#include "raymath.h"
#include "reasings.h"
#include "easings.h"

#define ARR_ASTEROIDS 100
#define ARR_BULLETS 150
#define ARR_EXPLOSIONS 15
#define ARR_UPGRADE_BTNS 3
#define ARR_XP_ORBS 100

using namespace std;

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
//#define DEBUGGING
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//#define ARR_SIZE(A) (sizeof(A)/sizeof(*(A)))

#define MAP_SIZE 14
#define MAP_OFFSET_X 200
#define MAP_OFFSET_Y 75

#define SPRITE_OFFSET ((8 * 6)/2)
#define SPRITE_SCALE_MULTI 6
#define SPRITE_SIZE 8
#define SPRITE_SIZE_SCALED 48
#define BUTTON_SPRITE_SIZE 32
#define BUTTON_SPRITE_OFFSET ((32 * 6)/2)

// red-thingy
//#define C_PLAYER 	CLITERAL(Color){ 175, 36, 71, 255 }
//#define C_ASTEROID 	CLITERAL(Color){ 107, 35, 65, 255 }
//#define C_BULLET 	CLITERAL(Color){ 238, 36, 61, 255 }
//#define C_CURSOR 	CLITERAL(Color){ 185, 36, 71, 255 }
//#define C_BG 		CLITERAL(Color){ 13, 16, 27, 255 }

//retrotronic
#define C_PLAYER 	CLITERAL(Color){ 72, 107, 127, 255 }
#define C_ASTEROID 	CLITERAL(Color){ 187, 71, 79, 255 }
//#define C_TEXT 		CLITERAL(Color){ 214, 36, 17, 255 }
#define C_TEXT 		CLITERAL(Color){ 188, 33, 106, 255 }
#define C_BULLET 	CLITERAL(Color){ 122, 156, 150, 255 }
#define C_CURSOR 	CLITERAL(Color){ 209, 191, 176, 255 }
#define C_BG 		CLITERAL(Color){ 4, 3, 3, 255}
#define C_BTN_HOVER CLITERAL(Color){ 200, 200, 200, 255}   // Button Highlight hover tint

namespace GLOBALS {
	//1024x758
	//const Vector2 SCREEN = { 840.0f, 480.0f };
	const Vector2 SCREEN = { 1024.0f, 768.0f };
	const string project_name = "Visual Asteroids";
}
