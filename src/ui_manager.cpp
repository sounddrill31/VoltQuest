#include "../include/ui_manager.hpp"
#include "../include/settings.hpp"
#include "raylib.h"
#include <cmath>

static float screenScale = 1.0f;
const float baseWidth = 1920;
const float baseHeight = 1080;
static Texture2D textures[IMGCOUNT];

void initUIManager() {
  textures[IMGLOGO] = LoadTexture("../assets/logos/VoltQuest.png");
  textures[IMGBUTTON] = LoadTexture("../assets/images/button.png");
  textures[IMGPANEL] = LoadTexture("../assets/images/panel.png");

  // Calculate scale of screen with respect to resolution
  screenScale =
      fminf(static_cast<float>(globalSettings.screenWidth / baseWidth),
            static_cast<float>(globalSettings.screenHeight / baseHeight));
}

void unloadAllUITexture() {
  for (int i = 0; i < IMGCOUNT; ++i) {
    UnloadTexture(textures[i]);
  }
}
void unloadUITexture(const int &IMG) { UnloadTexture(textures[IMG]); }

// Note:The buttonTexture image is in 3:1 RATIO so use appropriate resolution
void drawImageButton(const imageButton &button) {
  Rectangle scaledBounds = {
      button.bounds.x * screenScale, button.bounds.y * screenScale,
      button.bounds.width * screenScale, button.bounds.height * screenScale};

  DrawTexturePro(textures[IMGBUTTON],
                 {0, 0, static_cast<float>(textures[IMGBUTTON].width),
                  static_cast<float>(textures[IMGBUTTON].height)},
                 scaledBounds, {0, 0}, 0.0f, WHITE);
  if (button.isfocused) {
    DrawRectangleRoundedLines(scaledBounds, 0.5f, 3, SKYBLUE);
  }

  int scaledFontSize = static_cast<int>(button.fontSize * screenScale);
  int textWidth = MeasureText(button.text.c_str(), scaledFontSize);

  Vector2 textPos = {scaledBounds.x + (scaledBounds.width - textWidth) / 2.0f,
                     scaledBounds.y +
                         (scaledBounds.height - scaledFontSize) / 2.0f};

  DrawText(button.text.c_str(), static_cast<int>(textPos.x),
           static_cast<int>(textPos.y), scaledFontSize, button.textColor);
}

bool isImageButtonPressed(const imageButton &button) {
  bool ispressed = false;
  Rectangle scaledBounds = {
      button.bounds.x * screenScale, button.bounds.y * screenScale,
      button.bounds.width * screenScale, button.bounds.height * screenScale};

  Vector2 inputPos = GetMousePosition();
  bool isHovered = CheckCollisionPointRec(inputPos, scaledBounds);

  if (IsGestureDetected(GESTURE_TAP)) {
    inputPos = GetTouchPosition(0);
    isHovered = CheckCollisionPointRec(inputPos, scaledBounds);
  }

  if (isHovered && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ||
                    IsGestureDetected(GESTURE_TAP))) {
    ispressed = true;
  } else if (button.isfocused &&
             (IsKeyDown(KEY_ENTER) || IsKeyDown(KEY_KP_ENTER))) {
    ispressed = true;
  }
  return ispressed;
}

// Draw Image function
void drawImage(const int &IMG, const Rectangle &bounds) {
  Rectangle scaledBounds = {bounds.x * screenScale, bounds.y * screenScale,
                            bounds.width * screenScale,
                            bounds.height * screenScale};
  DrawTexturePro(textures[IMG],
                 {0.0f, 0.0f, static_cast<float>(textures[IMG].width),
                  static_cast<float>(textures[IMG].height)},
                 scaledBounds, {0.0f, 0.0f}, 0.0f, WHITE);
}

void updateKeyboardNavigation(imageButton *buttons, int count) {
  static int buttonFocused = 0;
}
