#include "../include/screen_manager.h"
#include "../include/ui_manager.h"
#include "../include/window_manager.h"
#include "raylib.h"
int main() {
  createWindow();
  initUIManager();
  while (!WindowShouldClose()) {
    BeginDrawing();
    drawStartMenu();
    EndDrawing();
  }
  unloadUITextures();
  CloseWindow();
  return 0;
}
