#ifndef UI_MANAGER_H
#define UI_MANAGER_H
#include "raylib.h"
#include <string>

struct imageButton {
  // The button Texture image is in 3:1 RATIO so use resolution in similar ratio
  Rectangle bounds;
  std::string text;
  int fontSize;
  Color textColor;
};
void initUIManager();
void unloadUITextures();
void drawImageButton(const imageButton &button);
bool isImageButtonPressed(const imageButton &button);
void drawLogo(Rectangle bounds);
#endif
