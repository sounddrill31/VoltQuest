#include "../include/screen_manager.hpp"
#include "../include/settings.hpp"
#include "../include/ui_manager.hpp"
#include "raylib.h"

const float screenW = 1920.0f;
const float screenH = 1080.0f;

enum class SCREEN { START_MENU, OPTIONS_MENU, CHAPTER_MENU, LEVEL_MENU, GAME };
SCREEN currentScreen = SCREEN::START_MENU;

namespace startMenu {
int focusedButton = 0;
const float logoSize = 450.0f;
static Vector2 buttonSize = {360.0f, 120.0f};
static Rectangle logoBounds = {screenW / 2.0f - startMenu::logoSize / 2.0f,
                               screenH / 2.0f - startMenu::logoSize,
                               startMenu::logoSize, startMenu::logoSize};

static imageButton playButton = {
    {screenW / 2.0f - startMenu::buttonSize.x / 2.0f, screenH / 2.0f,
     startMenu::buttonSize.x, startMenu::buttonSize.y},
    "PLAY",
    55,
    Color{255, 198, 0, 255}};

static imageButton optionsButton = {
    {screenW / 2.0f - startMenu::buttonSize.x / 2.0f, screenH / 2.0f + 160.f,
     startMenu::buttonSize.x, startMenu::buttonSize.y},
    "OPTIONS",
    55,
    Color{0, 146, 255, 255}};

static imageButton quitButton = {
    {screenW / 2.0f - startMenu::buttonSize.x / 2.0f, screenH / 2.0f + 320.f,
     startMenu::buttonSize.x, startMenu::buttonSize.y},
    "QUIT",
    55,
    RED};

imageButton *buttonsArray[] = {&playButton, &optionsButton, &quitButton};
} // namespace startMenu

namespace optionsMenu {
static Vector2 panelSize = {1000.0f, 900.0f};
static Rectangle panelBounds = {screenW / 2.0f - panelSize.x / 2.0f,
                                screenH / 2.0f - panelSize.y / 2.0f,
                                panelSize.x, panelSize.y};
static Vector2 optionsTextPos = {screenW / 2.0f, 140.0f};
} // namespace optionsMenu

void drawStartMenu() {
  ClearBackground(Color{58, 71, 80, 255});
  drawImage(IMGLOGO, startMenu::logoBounds);
  drawImageButton(startMenu::playButton);
  drawImageButton(startMenu::optionsButton);
  drawImageButton(startMenu::quitButton);
}

void drawOptionsMenu() {
  ClearBackground(Color{58, 71, 80, 255});
  drawImage(IMGPANEL, optionsMenu::panelBounds);
  drawUIText(80, optionsMenu::optionsTextPos, "OPTIONS",
             Color{0, 146, 255, 255});
}

void drawCurrentScreen() {
  switch (currentScreen) {
  case SCREEN::START_MENU: {
    drawStartMenu();
    updateKeyboardNavigation(3, startMenu::focusedButton,
                             startMenu::buttonsArray);
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
