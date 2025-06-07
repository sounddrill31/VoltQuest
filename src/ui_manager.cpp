#include "../include/ui_manager.hpp"
#include "../include/settings.hpp"
#include "../include/window_manager.hpp"
#include "raylib.h"
#include <cmath>
#include <string>

static float screenScale = 1.0f;
const float baseWidth = 1920;
const float baseHeight = 1080;
static Texture2D textures[IMGCOUNT];
static int buttonFocusedIndex = 0;

void initUIManager() {
  textures[IMGLOGO] =
      LoadTexture(getResourcePath("assets/logos/VoltQuest.png").c_str());
  textures[IMGBUTTON] =
      LoadTexture(getResourcePath("assets/images/button.png").c_str());
  textures[IMGPANEL] =
      LoadTexture(getResourcePath("assets/images/panel.png").c_str());

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

  if (button.isfocused) {
    DrawRectangleRoundedLinesEx(Rectangle{(button.bounds.x) * screenScale,
                                          (button.bounds.y) * screenScale,
                                          (button.bounds.width) * screenScale,
                                          (button.bounds.height) * screenScale},
                                0.18f, 5, 5.0f, SKYBLUE);
  }

  DrawTexturePro(textures[IMGBUTTON],
                 {0, 0, static_cast<float>(textures[IMGBUTTON].width),
                  static_cast<float>(textures[IMGBUTTON].height)},
                 scaledBounds, {0, 0}, 0.0f, WHITE);

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
    buttonFocusedIndex = 0;
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

void updateKeyboardNavigation(imageButton **buttons, int count) {
  if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && buttonFocusedIndex > 0) {
    --buttonFocusedIndex;
  }

  else if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) &&
           buttonFocusedIndex < count - 1) {
    ++buttonFocusedIndex;
  }
  for (int i = 0; i < count; ++i) {
    buttons[i]->isfocused = (i == buttonFocusedIndex);
  }
}
