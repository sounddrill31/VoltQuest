#include "../include/ui_manager.hpp"
#include "../include/path_utils.hpp"
#include "../include/settings.hpp"
#include "raylib.h"
#include <cmath>
#include <string>

const float baseWidth = 1920.0f;
const float baseHeight = 1080.0f;
static float screenScaleX = 1.0f;
static float screenScaleY = 1.0f;
static Texture2D textures[IMGCOUNT];

// Utils
void calculateScreenScale() {
  // Calculate scale of screen with respect to resolution
  screenScaleX = static_cast<float>(globalSettings.screenWidth / baseWidth);
  screenScaleY = static_cast<float>(globalSettings.screenHeight / baseHeight);
}

// Manage Textures
void loadAllUITextures() {
  textures[IMGLOGO] =
      LoadTexture(getResourcePath("assets/logos/VoltQuest.png").c_str());
  textures[IMGBUTTON] =
      LoadTexture(getResourcePath("assets/images/button.png").c_str());
  textures[IMGPANEL] =
      LoadTexture(getResourcePath("assets/images/panel.png").c_str());
}

void loadUITexture(int IMG_ID, const std::string &texturePath) {
  textures[IMG_ID] = LoadTexture(getResourcePath(texturePath).c_str());
}

void unloadAllUITexture() {
  for (int i = 0; i < IMGCOUNT; ++i) {
    UnloadTexture(textures[i]);
  }
}

void unloadUITexture(int IMG_ID) { UnloadTexture(textures[IMG_ID]); }

// Draw Functions
void drawImageButton(const imageButton &button) {
  Rectangle scaledBounds = {
      button.bounds.x * screenScaleX, button.bounds.y * screenScaleY,
      button.bounds.width * screenScaleX, button.bounds.height * screenScaleY};

  if (button.isfocused) {
    DrawRectangleRoundedLinesEx(scaledBounds, 0.18f, 6,
                                5.0f * ((screenScaleX + screenScaleY) / 2.0f),
                                SKYBLUE);
  }

  DrawTexturePro(textures[IMGBUTTON],
                 {0, 0, static_cast<float>(textures[IMGBUTTON].width),
                  static_cast<float>(textures[IMGBUTTON].height)},
                 scaledBounds, {0, 0}, 0.0f, WHITE);

  int scaledFontSize =
      static_cast<int>(button.fontSize * fminf(screenScaleX, screenScaleY));
  int textWidth = MeasureText(button.text.c_str(), scaledFontSize);

  Vector2 textPos = {scaledBounds.x + (scaledBounds.width - textWidth) / 2.0f,
                     scaledBounds.y +
                         (scaledBounds.height - scaledFontSize) / 2.0f};

  DrawText(button.text.c_str(), static_cast<int>(textPos.x),
           static_cast<int>(textPos.y), scaledFontSize, button.textColor);
}

void drawImage(int IMG_ID, const Rectangle &bounds) {
  Rectangle scaledBounds = {bounds.x * screenScaleX, bounds.y * screenScaleY,
                            bounds.width * screenScaleX,
                            bounds.height * screenScaleY};
  DrawTexturePro(textures[IMG_ID],
                 {0.0f, 0.0f, static_cast<float>(textures[IMG_ID].width),
                  static_cast<float>(textures[IMG_ID].height)},
                 scaledBounds, {0.0f, 0.0f}, 0.0f, WHITE);
}

void drawUIText(int fontSize, const Vector2 &textPos, const std::string &text,
                const Color &textColor) {
  int scaledFontSize =
      static_cast<int>(fontSize * fminf(screenScaleX, screenScaleY));
  int textWidth = MeasureText(text.c_str(), scaledFontSize);

  DrawText(text.c_str(),
           static_cast<int>((textPos.x * screenScaleX - textWidth / 2.0f)),
           static_cast<int>(textPos.y * screenScaleY), scaledFontSize,
           textColor);
}

// Input Functions
bool isImageButtonPressed(const imageButton &button) {
  bool ispressed = false;
  Rectangle scaledBounds = {
      button.bounds.x * screenScaleX, button.bounds.y * screenScaleY,
      button.bounds.width * screenScaleX, button.bounds.height * screenScaleY};

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

void updateKeyboardNavigation(int count, int &focusedButton,
                              imageButton **buttons) {
  if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && focusedButton > 0) {
    --focusedButton;
  }

  else if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) &&
           focusedButton < count - 1) {
    ++focusedButton;
  }
  for (int i = 0; i < count; ++i) {
    buttons[i]->isfocused = (i == focusedButton);
  }
}
