#include "../include/screen_manager.h"
#include "../include/settings.h"
#include "../include/ui_manager.h"
#include "raylib.h"

static const float startMenuLogoSize = 450.0f;

static const Rectangle startMenuLogoBounds = {
    (float)globalSettings.screenWidth / 2.0f - (startMenuLogoSize / 2.0f),
    (float)globalSettings.screenHeight / 2.0f - startMenuLogoSize,
    startMenuLogoSize, startMenuLogoSize};

static const Vector2 startMenuButtonSize = {360.0f, 120.0f};

static const imageButton playButton = {
    {(float)globalSettings.screenWidth / 2.0f - (startMenuButtonSize.x / 2.0f),
     (float)globalSettings.screenHeight / 2.0f, startMenuButtonSize.x,
     startMenuButtonSize.y},
    "PLAY",
    55,
    (Color){255, 198, 0, 255}};

static const imageButton optionsButton = {
    {(float)globalSettings.screenWidth / 2.0f - (startMenuButtonSize.x / 2.0f),
     (float)globalSettings.screenHeight / 2.0f + 160.f, startMenuButtonSize.x,
     startMenuButtonSize.y},
    "OPTIONS",
    55,
    (Color){0, 146, 255, 255}};

static const imageButton quitButton = {
    {(float)globalSettings.screenWidth / 2.0f - (startMenuButtonSize.x / 2.0f),
     (float)globalSettings.screenHeight / 2.0f + 320.f, startMenuButtonSize.x,
     startMenuButtonSize.y},
    "QUIT",
    55,
    RED};

void drawStartMenu() {
  ClearBackground((Color){58, 71, 80, 255});
  drawLogo(startMenuLogoBounds);
  drawImageButton(playButton);
  drawImageButton(optionsButton);
  drawImageButton(quitButton);
}
