#ifndef SETTINGS_H
#define SETTINGS_H

struct settings {
  bool isGameRunning;
  int currentMonitor;
  int monitorWidth;
  int monitorHeight;
  int screenWidth;
  int screenHeight;
  int RefreshRate;
  bool fullscreen;
};

inline settings globalSettings = {.isGameRunning = true,
                                  .currentMonitor = 0,
                                  .screenWidth = 1920,
                                  .screenHeight = 1080,
                                  .RefreshRate = 60,
                                  .fullscreen = false};

#endif
