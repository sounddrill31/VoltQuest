#include "../include/window_manager.hpp"
#include "../include/settings.hpp"
#include <filesystem>
#include <raylib.h>
#include <string>

static std::string basePath;

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

void initBasePath() { basePath = std::filesystem::current_path().string(); }

std::string getResourcePath(const std::string &relativePath) {
  return basePath + "/resources/" + relativePath;
}
