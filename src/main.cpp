#include "../include/screen_manager.h"
#include "../include/settings.h"
#include "../include/ui_manager.h"
#include "../include/window_manager.h"
#include "raylib.h"
int main() {
  createWindow();
  initUIManager();
  initScreenManager();

  while (globalSettings.isGameRunning) {
    BeginDrawing();
    drawCurrentScreen();
    EndDrawing();
  }
  unloadUITextures();
  CloseWindow();
  return 0;
}
