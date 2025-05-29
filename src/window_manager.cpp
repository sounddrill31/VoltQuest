#include "../include/window_manager.h"
#include "../include/settings.h"
#include <raylib.h>

void createWindow() {
  // Create a temporary window to retrieve monitor info, then close it
  InitWindow(1, 1, "temp");
  globalSettings.currentMonitor = GetCurrentMonitor();
  globalSettings.screenWidth = GetMonitorWidth(globalSettings.currentMonitor);
  globalSettings.screenHeight = GetMonitorHeight(globalSettings.currentMonitor);
  CloseWindow();

  // forcing the resolution tobe nearest 16:9 resolution
  int forcedHeight = globalSettings.screenHeight;
  int forcedWidth = (forcedHeight * 16) / 9;

  if (forcedWidth > globalSettings.screenWidth) {
    forcedWidth = globalSettings.screenWidth;
    forcedHeight = (forcedWidth * 9) / 16;
  }

  // Save the forced resolution
  globalSettings.screenWidth = forcedWidth;
  globalSettings.screenHeight = forcedHeight;

  // Create a the game window
  InitWindow(globalSettings.screenWidth, globalSettings.screenHeight,
             "VoltQuest");
  SetTargetFPS(globalSettings.RefreshRate);
}
