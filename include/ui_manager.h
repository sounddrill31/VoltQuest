#ifndef UI_MANAGER_H
#define UI_MANAGER_H
#include "raylib.h"
#include <string>

constexpr int IMGLOGO = 0;
constexpr int IMGBUTTON = 1;
constexpr int IMGPANEL = 2;
constexpr int IMGCOUNT = 3;

struct imageButton {
  // The button Texture image is in 3:1 RATIO so use resolution in similar ratio
  Rectangle bounds;
  std::string text;
  int fontSize;
  Color textColor;
};
void initUIManager();
void unloadAllUITexture();
void unloadUITexture(int IMG);
void drawImageButton(const imageButton &button);
bool isImageButtonPressed(const imageButton &button);
void drawImage(int IMG, Rectangle bounds);

#endif
