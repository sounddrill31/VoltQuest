#include "../include/game_objects/electronic_components/output/led.hpp"
#include "../include/game_objects/electronic_components/power/battery.hpp"
#include "../include/game_objects/electronic_components/wiring/wire.hpp"
#include "../include/ui_manager.hpp"
#include "../include/ui_utils.hpp"
#include "raylib.h"
#include <memory>
#include <vector>

// Global state
std::vector<std::shared_ptr<MovableObject>> objects;
std::shared_ptr<MovableObject> activeObject = nullptr;
std::vector<Wire> wires;

bool isPlacingWire = false;
std::shared_ptr<MovableObject> wireStartObject = nullptr;
bool wireFromPositive = true;

// Reset level to a clean state with default objects
void resetLevel() {
  objects.clear();
  wires.clear();
  activeObject = nullptr;
  isPlacingWire = false;
  wireStartObject = nullptr;
}

void updateLevel() {
  ClearBackground(GRAY);
  Vector2 mousePos = GetMousePosition();

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    // Check if user clicked on a positive or negative pin of any object
    for (auto &obj : objects) {
      if (CheckCollisionPointRec(mousePos, obj->getPositiveCollider())) {
        if (!isPlacingWire) {
          wireStartObject = obj;
          wireFromPositive = true;
          isPlacingWire = true;
        } else if (wireStartObject != obj) {
          wires.emplace_back(wireStartObject, obj, wireFromPositive, true);
          isPlacingWire = false;
          wireStartObject = nullptr;
        }
        return;
      }
      if (CheckCollisionPointRec(mousePos, obj->getNegativeCollider())) {
        if (!isPlacingWire) {
          wireStartObject = obj;
          wireFromPositive = false;
          isPlacingWire = true;
        } else if (wireStartObject != obj) {
          wires.emplace_back(wireStartObject, obj, wireFromPositive, false);
          isPlacingWire = false;
          wireStartObject = nullptr;
        }
        return;
      }
    }

    // If no pin clicked, check if user clicked on an object to select it
    for (int i = (int)objects.size() - 1; i >= 0; i--) {
      if (CheckCollisionPointRec(mousePos, objects[i]->getCollider())) {
        if (activeObject)
          activeObject->isActive = false;

        objects[i]->isActive = true;
        activeObject = objects[i];
        break;
      }
    }
  }

  for (int i = (int)objects.size() - 1; i >= 0; i--) {
    objects[i]->update();
  }
  for (auto &obj : objects) {
    obj->loadObjectTexture();
    obj->draw();
  }

  // Draw all wires
  for (const Wire &wire : wires) {
    wire.draw();
  }

  // Draw preview wire if currently placing one
  if (isPlacingWire && wireStartObject) {
    Vector2 start = wireFromPositive
                        ? wireStartObject->getPositivePinPosition()
                        : wireStartObject->getNegativePinPosition();
    Vector2 end = mousePos;

    DrawLineEx(start, end, 6.0f, BLACK);
    DrawLineEx(start, end, 4.0f, RED);
  }

  // Draw inspector with Reset button
  drawComponentsPanel(objects, activeObject, wires, isPlacingWire,
                      wireStartObject);
}
