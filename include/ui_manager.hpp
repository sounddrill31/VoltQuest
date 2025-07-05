#ifndef UI_MANAGER_H
#define UI_MANAGER_H
#include "raylib.h"
#include <string>

constexpr int IMGLOGO = 0;
constexpr int IMGCOUNT = 1;

struct UIButton {
  Rectangle bounds;
  std::string text;
  int fontSize;
  Color textColor;
  bool isfocused;
};

// Utils
void calculateScreenScale();

// Manage Textures

void loadAllUITextures();
void loadUITexture(int IMG_ID, const std::string &texturePath);
void unloadAllUITexture();
void unloadUITexture(int IMG_ID);

// Draw Functions
void drawUIRect(float outlineSize, const Rectangle &bounds);
void drawUIButton(const UIButton &button);
void drawImage(int IMG_ID, const Rectangle &bounds);
void drawUIPanel(float outlineSize, const Rectangle &bounds);
void drawUIText(int fontSize, const Vector2 &textPos, const std::string &text,
                const Color &textColor);

// Input Functions
bool isUIButtonPressed(const UIButton &button);
void updateKeyboardNavigation(int count, int &focusedButton,
                              UIButton **buttons);

#endif
