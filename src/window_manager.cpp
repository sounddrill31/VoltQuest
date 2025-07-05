#include "../include/window_manager.hpp"
#include "../include/settings.hpp"
#include "raylib.h"

void createWindow() {
  // Create a temporary window to retrieve monitor info, then close it
  InitWindow(1, 1, "temp");
  globalSettings.currentMonitor = GetCurrentMonitor();
  globalSettings.monitorWidth = GetMonitorWidth(globalSettings.currentMonitor);
  globalSettings.monitorHeight =
      GetMonitorHeight(globalSettings.currentMonitor);
  CloseWindow();

  if (overrideSettings()) {
    globalSettings.screenWidth = globalSettings.monitorWidth;
    globalSettings.screenHeight = globalSettings.monitorHeight;
    globalSettings.refreshRate = 60;
    globalSettings.fullscreen = true;
    saveSettings();
  }

  if (globalSettings.fullscreen) {
    globalSettings.screenWidth = globalSettings.monitorWidth;
    globalSettings.screenHeight = globalSettings.monitorHeight;
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
  } else {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  }

  // Create a the game window
  InitWindow(globalSettings.screenWidth, globalSettings.screenHeight,
             "VoltQuest");

  SetExitKey(0); // Disables Escape key from CloseWindow
  SetTargetFPS(globalSettings.refreshRate);
}
