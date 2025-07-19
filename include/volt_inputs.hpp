#ifndef VOLT_INPUT_HPP
#define VOLT_INPUT_HPP

#include "ui_utils.hpp"
#include <raylib.h>

struct VoltInput;
inline VoltInput *activeDrag = nullptr;

struct VoltInput {
  bool dragging = false;
  Vector2 dragOffset = {0, 0};

  void mouseDragRect(Rectangle collision, Vector2 &position) {
    Vector2 inputPos;
    bool inputDown = false;
    bool inputPressed = false;
    bool inputReleased = false;

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      inputPos = GetMousePosition();
      inputDown = true;
      inputPressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
      inputReleased = IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
    } else if (GetTouchPointCount() > 0) {
      inputPos = GetTouchPosition(0);
      inputDown = true;

      if (!dragging)
        inputPressed = true;
    } else {
      if (dragging)
        inputReleased = true;
    }

    // Only start dragging if no other object is dragging
    if (inputPressed && CheckCollisionPointRec(inputPos, collision)) {
      if (activeDrag == nullptr) {
        dragOffset = {inputPos.x - position.x, inputPos.y - position.y};
        dragging = true;
        activeDrag = this;
      }
    }

    // Only allow this object to continue dragging if it was the one that
    // started
    if (inputReleased && dragging) {
      dragging = false;
      if (activeDrag == this) {
        activeDrag = nullptr;
      }
    }

    if (dragging && inputDown && activeDrag == this) {
      position = {inputPos.x - dragOffset.x, inputPos.y - dragOffset.y};
    }
  }
};

#endif
