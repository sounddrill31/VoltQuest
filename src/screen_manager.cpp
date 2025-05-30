#include "../include/screen_manager.h"
#include "../include/settings.h"
#include "../include/ui_manager.h"
#include "raylib.h"

static Rectangle startMenuLogoBounds;
static imageButton playButton;
static imageButton optionsButton;
static imageButton quitButton;

void initScreenManager() {
  // StartMenu Variable Declarations
  float screenW = (float)globalSettings.screenWidth;
  float screenH = (float)globalSettings.screenHeight;

  const float logoSize = 450.0f;
  startMenuLogoBounds = {screenW / 2.0f - logoSize / 2.0f,
                         screenH / 2.0f - logoSize, logoSize, logoSize};

  const Vector2 buttonSize = {360.0f, 120.0f};

  playButton = {{screenW / 2.0f - buttonSize.x / 2.0f, screenH / 2.0f,
                 buttonSize.x, buttonSize.y},
                "PLAY",
                55,
                (Color){255, 198, 0, 255}};

  optionsButton = {{screenW / 2.0f - buttonSize.x / 2.0f,
                    screenH / 2.0f + 160.f, buttonSize.x, buttonSize.y},
                   "OPTIONS",
                   55,
                   (Color){0, 146, 255, 255}};

  quitButton = {{screenW / 2.0f - buttonSize.x / 2.0f, screenH / 2.0f + 320.f,
                 buttonSize.x, buttonSize.y},
                "QUIT",
                55,
                RED};
  //
}

void drawStartMenu() {
  ClearBackground((Color){58, 71, 80, 255});
  drawLogo(startMenuLogoBounds);
  drawImageButton(playButton);
  drawImageButton(optionsButton);
  drawImageButton(quitButton);
}
