#include "../include/window_manager.hpp"
#include "../include/settings.hpp"
#include "raylib.h"


void createWindow() {
  // Create a temporary window to retrieve monitor info, then close it
  InitWindow(1, 1, "temp");
  globalSettings.currentMonitor = GetCurrentMonitor();
  globalSettings.screenWidth = GetMonitorWidth(globalSettings.currentMonitor);
  globalSettings.screenHeight = GetMonitorHeight(globalSettings.currentMonitor);
  CloseWindow();

  // Create a the game window
  InitWindow(globalSettings.screenWidth, globalSettings.screenHeight,
             "VoltQuest");
  SetExitKey(0); // Disables Escape key from CloseWindow
  SetTargetFPS(globalSettings.RefreshRate);
}


