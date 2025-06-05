#include "../include/screen_manager.h"
#include "../include/settings.h"
#include "../include/ui_manager.h"
#include "../include/window_manager.h"
#include "raylib.h"
int main() {
  createWindow();
  initUIManager();
  while (globalSettings.isGameRunning) {
    BeginDrawing();
    drawCurrentScreen();
    EndDrawing();
  }
  unloadAllUITexture();
  CloseWindow();
  return 0;
}
