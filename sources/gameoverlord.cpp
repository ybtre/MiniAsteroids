#include "GameOverlord.h"

GameOverlord::GameOverlord() {
  current_screen = MAIN_MENU;

  score = 0;

  is_paused = false;
};

void GameOverlord::SetupGame() {
  score = 0;

  live_src = {32, 0, SPRITE_SIZE, SPRITE_SIZE};
  live_dest = {10, 40, live_src.width * SPRITE_SCALE_MULTI,
               live_src.height * SPRITE_SCALE_MULTI};

  score_src = {SPRITE_SIZE_SCALED, 0, SPRITE_SIZE, SPRITE_SIZE};
  score_dest = {10, 100, score_src.width * SPRITE_SCALE_MULTI,
                score_src.height * SPRITE_SCALE_MULTI};
}

void GameOverlord::ResetGame() {
  score = 0;

  is_paused = false;
};

GameOverlord::SCREENS GameOverlord::GetCurrentScreen() {
  return current_screen;
};

void GameOverlord::SetCurrentScreen(const SCREENS new_screen) {
  current_screen = new_screen;
};

bool GameOverlord::IsGameOver() { return false; }
