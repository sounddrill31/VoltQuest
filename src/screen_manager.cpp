#include "../include/screen_manager.h"
#include "../include/settings.h"
#include "../include/ui_manager.h"
#include "raylib.h"

enum class SCREEN { START_MENU, OPTIONS_MENU, CHAPTER_MENU, LEVEL_MENU, GAME };
SCREEN currentScreen = SCREEN::START_MENU;

namespace startMenu {
static Rectangle logoBounds;
static imageButton playButton;
static imageButton optionsButton;
static imageButton quitButton;
} // namespace startMenu

const float screenW = 1920.0f;
const float screenH = 1080.0f;

void initScreenManager() {
  globalSettings.isGameRunning = true;
  // StartMenu Variables

  const float logoSize = 450.0f;
  startMenu::logoBounds = {screenW / 2.0f - logoSize / 2.0f,
                           screenH / 2.0f - logoSize, logoSize, logoSize};

  const Vector2 buttonSize = {360.0f, 120.0f};

  startMenu::playButton = {{screenW / 2.0f - buttonSize.x / 2.0f,
                            screenH / 2.0f, buttonSize.x, buttonSize.y},
                           "PLAY",
                           55,
                           (Color){255, 198, 0, 255}};

  startMenu::optionsButton = {{screenW / 2.0f - buttonSize.x / 2.0f,
                               screenH / 2.0f + 160.f, buttonSize.x,
                               buttonSize.y},
                              "OPTIONS",
                              55,
                              (Color){0, 146, 255, 255}};

  startMenu::quitButton = {{screenW / 2.0f - buttonSize.x / 2.0f,
                            screenH / 2.0f + 320.f, buttonSize.x, buttonSize.y},
                           "QUIT",
                           55,
                           RED};
  //
}

void drawStartMenu() {
  ClearBackground((Color){58, 71, 80, 255});
  drawLogo(startMenu::logoBounds);
  drawImageButton(startMenu::playButton);
  drawImageButton(startMenu::optionsButton);
  drawImageButton(startMenu::quitButton);
}

void drawOptionsMenu() {
  ClearBackground((Color){58, 71, 80, 255});
  DrawRectangleRounded(
      {screenW / 2.0f - 600.0f, screenH / 2.0f - 400.0f, 1200.0f, 800.0f}, 0.2f,
      1, LIGHTGRAY);
}

void drawCurrentScreen() {
  switch (currentScreen) {
  case SCREEN::START_MENU: {
    drawStartMenu();
    if (isImageButtonPressed(startMenu::playButton)) {
      currentScreen = SCREEN::CHAPTER_MENU;
    }

    else if (isImageButtonPressed(startMenu::optionsButton)) {
      currentScreen = SCREEN::OPTIONS_MENU;
    }

    else if (isImageButtonPressed(startMenu::quitButton)) {
      globalSettings.isGameRunning = false;
    }
    break;
  }
  case SCREEN::OPTIONS_MENU: {
    drawOptionsMenu();
    if (IsKeyDown(KEY_ESCAPE)) {
      currentScreen = SCREEN::START_MENU;
    }
    break;
  }
  }
}
