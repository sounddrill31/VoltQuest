#include "../include/ui_manager.h"
#include "../include/settings.h"
#include "raylib.h"
#include <cmath>

static Texture2D logoTexture;
static Texture2D buttonTexture;
static float screenScale{1.0f};
const int baseWidth{1920};
const int baseHeight{1080};

void initUIManager() {
  buttonTexture = LoadTexture("../assets/images/button.png");
  logoTexture = LoadTexture("../assets/logos/VoltQuest.png");

  // Calculate scale of screen with respect to resolution
  screenScale = fminf((float)globalSettings.screenWidth / baseWidth,
                      (float)globalSettings.screenHeight / baseHeight);
}

void unloadUITextures() {
  UnloadTexture(buttonTexture);
  UnloadTexture(logoTexture);
}

// Note:The buttonTexture image is in 3:1 RATIO so use appropriate resolution
void drawImageButton(const imageButton &button) {
  Rectangle scaledBounds = {
      button.bounds.x * screenScale, button.bounds.y * screenScale,
      button.bounds.width * screenScale, button.bounds.height * screenScale};

  DrawTexturePro(
      buttonTexture,
      {0, 0, (float)buttonTexture.width, (float)buttonTexture.height},
      scaledBounds, {0, 0}, 0.0f, WHITE);

  int scaledFontSize = (int)(button.fontSize * screenScale);
  int textWidth = MeasureText(button.text.c_str(), scaledFontSize);

  Vector2 textPos = {scaledBounds.x + (scaledBounds.width - textWidth) / 2.0f,
                     scaledBounds.y +
                         (scaledBounds.height - scaledFontSize) / 2.0f};

  DrawText(button.text.c_str(), (int)textPos.x, (int)textPos.y, scaledFontSize,
           button.textColor);
}

bool isImageButtonPressed(const imageButton &button) {
  Rectangle scaledBounds = {
      button.bounds.x * screenScale, button.bounds.y * screenScale,
      button.bounds.width * screenScale, button.bounds.height * screenScale};

  Vector2 inputPos = GetMousePosition();
  bool isHovered = CheckCollisionPointRec(inputPos, scaledBounds);

  if (IsGestureDetected(GESTURE_TAP)) {
    inputPos = GetTouchPosition(0);
    isHovered = CheckCollisionPointRec(inputPos, scaledBounds);
  }

  return isHovered && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ||
                       IsGestureDetected(GESTURE_TAP));
}

void drawLogo(Rectangle bounds) {
  Rectangle scaledBounds = {bounds.x * screenScale, bounds.y * screenScale,
                            bounds.width * screenScale,
                            bounds.height * screenScale};
  DrawTexturePro(
      logoTexture,
      {0.0f, 0.0f, (float)logoTexture.width, (float)logoTexture.height},
      scaledBounds, {0.0f, 0.0f}, 0.0f, WHITE);
}
