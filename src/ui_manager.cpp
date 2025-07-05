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
static float safeScreenScale = 1.0f;
static Texture2D textures[IMGCOUNT];

// ─────────────────────────────────────────────────────
// Utils
// ─────────────────────────────────────────────────────
void calculateScreenScale() {
  screenScaleX = static_cast<float>(globalSettings.screenWidth) / baseWidth;
  screenScaleY = static_cast<float>(globalSettings.screenHeight) / baseHeight;
  safeScreenScale = (screenScaleX + screenScaleY) / 2.0f;
}

// ─────────────────────────────────────────────────────
// Manage Textures
// ─────────────────────────────────────────────────────
void loadAllUITextures() {
  textures[IMGLOGO] =
      LoadTexture(getResourcePath("assets/logos/VoltQuest.png").c_str());
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

// ─────────────────────────────────────────────────────
// Draw Functions
// ─────────────────────────────────────────────────────
void drawUIRect(float outlineSize, const Rectangle &bounds) {
  DrawRectangleRounded(bounds, 0.2f, 6, Color{151, 151, 165, 255});

  DrawRectangleRounded(
      Rectangle{bounds.x + (outlineSize * safeScreenScale) / 2.0f,
                bounds.y + (outlineSize * safeScreenScale) / 2.0f,
                bounds.width - outlineSize * safeScreenScale,
                bounds.height - outlineSize * safeScreenScale},
      0.2f, 6, WHITE);

  DrawRectangleRounded(
      Rectangle{bounds.x + ((outlineSize * 2.0f) * safeScreenScale) / 2.0f,
                bounds.y + ((outlineSize * 2.0f) * safeScreenScale) / 2.0f,
                bounds.width - (outlineSize * 2.0f) * safeScreenScale,
                bounds.height - (outlineSize * 2.0f) * safeScreenScale},
      0.2f, 6, Color{219, 221, 232, 255});
}

void drawUIButton(const UIButton &button) {

  if (button.isfocused) {
    DrawRectangleRoundedLinesEx(
        button.bounds, 0.2f, 6,
        5.0f * safeScreenScale, // consistent outline thickness
        SKYBLUE);
  }

  drawUIRect(12.0f, button.bounds);

  int scaledFontSize = static_cast<int>(button.fontSize * safeScreenScale);
  int textWidth = MeasureText(button.text.c_str(), scaledFontSize);

  Vector2 textPos = {button.bounds.x + (button.bounds.width - textWidth) / 2.0f,
                     button.bounds.y +
                         (button.bounds.height - scaledFontSize) / 2.0f};

  DrawText(button.text.c_str(), static_cast<int>(textPos.x),
           static_cast<int>(textPos.y), scaledFontSize, button.textColor);
}

void drawUIPanel(float outlineSize, const Rectangle &bounds) {
  drawUIRect(outlineSize, bounds);
}

void drawImage(int IMG_ID, const Rectangle &bounds) {

  DrawTexturePro(textures[IMG_ID],
                 {0.0f, 0.0f, static_cast<float>(textures[IMG_ID].width),
                  static_cast<float>(textures[IMG_ID].height)},
                 bounds, {0.0f, 0.0f}, 0.0f, WHITE);
}

void drawUIText(int fontSize, const Vector2 &textPos, const std::string &text,
                const Color &textColor) {
  int scaledFontSize = static_cast<int>(fontSize * safeScreenScale);
  int textWidth = MeasureText(text.c_str(), scaledFontSize);

  DrawText(text.c_str(), static_cast<int>(textPos.x - textWidth / 2.0f),
           static_cast<int>(textPos.y), scaledFontSize, textColor);
}

// ─────────────────────────────────────────────────────
// Input Functions
// ─────────────────────────────────────────────────────
bool isUIButtonPressed(const UIButton &button) {

  Vector2 inputPos = GetMousePosition();
  bool isHovered = CheckCollisionPointRec(inputPos, button.bounds);

  if (IsGestureDetected(GESTURE_TAP)) {
    inputPos = GetTouchPosition(0);
    isHovered = CheckCollisionPointRec(inputPos, button.bounds);
  }

  if (isHovered && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ||
                    IsGestureDetected(GESTURE_TAP))) {
    return true;
  }

  if (button.isfocused && (IsKeyDown(KEY_ENTER) || IsKeyDown(KEY_KP_ENTER))) {
    return true;
  }

  return false;
}

void updateKeyboardNavigation(int count, int &focusedButton,
                              UIButton **buttons) {
  if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && focusedButton > 0) {
    --focusedButton;
  } else if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) &&
             focusedButton < count - 1) {
    ++focusedButton;
  }

  for (int i = 0; i < count; ++i) {
    buttons[i]->isfocused = (i == focusedButton);
  }
}
