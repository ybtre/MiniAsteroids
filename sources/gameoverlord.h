#pragma once
#include "globals.h"

#define ARR_WAVES 10

typedef struct AWave {
  int level;
  float duration;
  float enemy_spawn_interval;
} AWave;

class GameOverlord {
public:
  enum SCREENS { MAIN_MENU = 0, GAMEPLAY = 1, GAME_OVER = 2, UPGRADE = 3 };

  GameOverlord();

  void SetupGame();
  bool IsGameOver();
  void ResetGame();

  SCREENS GetCurrentScreen();
  void SetCurrentScreen(SCREENS new_screen);

  SCREENS current_screen{};

  int score{};

  bool is_paused = false;
  int pause_blink_counter = 0;

  int current_wave = 0;
  float gameplay_time_total = 0;
  float gameplay_time_current = 0;
  float wave_duration = 0.f;
  bool is_wave_starting = false;
  // bool has_wave_finished = false;
  AWave waves[ARR_WAVES] = {
      {1, 10.9f, 1.f},   {2, 12.9f, .8f}, {3, 14.9f, .7f},  {4, 16.9f, .65f},
      {5, 20.9f, .625f}, {6, 25.9f, .6f}, {7, 35.9f, .55f}, {8, 40.9f, .5f},
      {9, 50.9f, .4f},   {10, 60.9f, .2f}};

  Rectangle live_src;
  Rectangle live_dest;
  Rectangle score_src;
  Rectangle score_dest;
};
