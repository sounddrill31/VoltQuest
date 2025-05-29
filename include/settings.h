#ifndef SETTINGS_H
#define SETTINGS_H

struct settings {
  int currentMonitor = 0;
  int screenWidth = 1920;
  int screenHeight = 1080;
  int RefreshRate = 60;
  bool fullscreen = false;
};

inline settings globalSettings;

#endif
