#ifndef UI_UTILS_HPP
#define UI_UTILS_HPP

#include "../include/settings.hpp"

// Constants
constexpr float baseWidth = 1920.0f;
constexpr float baseHeight = 1080.0f;

// Global screen scale factors (shared)
inline float screenScaleX = 1.0f;
inline float screenScaleY = 1.0f;
inline float safeScreenScale = 1.0f;

// Inline function to calculate scale
inline void calculateScreenScale() {
  screenScaleX = static_cast<float>(globalSettings.screenWidth) / baseWidth;
  screenScaleY = static_cast<float>(globalSettings.screenHeight) / baseHeight;
  safeScreenScale = (screenScaleX + screenScaleY) / 2.0f;
}

#endif // UI_UTILS_HPP
