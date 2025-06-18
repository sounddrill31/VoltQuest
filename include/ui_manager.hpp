#ifndef UI_MANAGER_H
#define UI_MANAGER_H
#include "raylib.h"
#include <string>

constexpr int IMGLOGO = 0;
constexpr int IMGBUTTON = 1;
constexpr int IMGPANEL = 2;
constexpr int IMGCOUNT = 3;

struct imageButton {
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
void drawImageButton(const imageButton &button);
void drawImage(int IMG_ID, const Rectangle &bounds);
void drawUIText(int fontSize, const Vector2 &textPos, const std::string &text,
                const Color &textColor);

// Input Functions
bool isImageButtonPressed(const imageButton &button);
void updateKeyboardNavigation(int count, int &focusedButton,
                              imageButton **buttons);

#endif
