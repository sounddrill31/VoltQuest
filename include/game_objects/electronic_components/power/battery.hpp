#ifndef BATTERY_HPP
#define BATTERY_HPP

#include "../../../../include/path_utils.hpp"
#include "../../../../include/ui_utils.hpp"
#include "../../../../include/volt_inputs.hpp"
#include "../../movable_object.hpp"
#include <raylib.h>
#include <string>

struct Battery : public MovableObject {
  float voltage;
  float current;
  bool status;
  VoltInput inputs;
  inline static Texture2D sharedTexture = {0};

  Rectangle collider = {position.x, position.y, 75.0f * safeScreenScale,
                        299.0f * safeScreenScale};
  Rectangle positiveCollider = {position.x + 35.0f, position.y + 1.0f,
                                6.0f * safeScreenScale, 6.0f * safeScreenScale};
  Rectangle negativeCollider = {position.x + 35.0f, position.y + 294.0f,
                                6.0f * safeScreenScale, 6.0f * safeScreenScale};

  Battery(Vector2 pos = {0, 0}, float volt = 1.5f, float curr = 1.0f,
          bool stat = true)
      : MovableObject(pos), voltage(volt), current(curr), status(stat) {}

  void loadObjectTexture() override {
    if (sharedTexture.id == 0) {
      sharedTexture =
          LoadTexture(getResourcePath("assets/images/battery.png").c_str());
    }
    texture = sharedTexture;
  }

  Rectangle getCollider() const override { return collider; }
  Rectangle getPositiveCollider() const override { return positiveCollider; }

  Rectangle getNegativeCollider() const override { return negativeCollider; }

  void update() override {
    inputs.mouseDragRect(collider, position);
    collider.x = position.x;
    collider.y = position.y;
    positiveCollider.x = position.x + 35.0f;
    positiveCollider.y = position.y + 1.0f;
    negativeCollider.x = position.x + 35.0f;
    negativeCollider.y = position.y + 294.0f;
  }

  void draw() override {
    DrawTexturePro(texture,
                   {0.0f, 0.0f, static_cast<float>(texture.width),
                    static_cast<float>(texture.height)},
                   {position.x, position.y, texture.width * safeScreenScale,
                    texture.height * safeScreenScale},
                   {0.0f, 0.0f}, 0.0f, WHITE);
    DrawRectangle(positiveCollider.x, positiveCollider.y,
                  positiveCollider.width, positiveCollider.height, WHITE);
    DrawRectangle(negativeCollider.x, negativeCollider.y,
                  negativeCollider.width, negativeCollider.height, WHITE);
    if (isActive) {
      DrawRectangleLinesEx(
          Rectangle{(position.x - 5.0f) * safeScreenScale,
                    (position.y - 5.0f) * safeScreenScale,
                    (texture.width + 10.0f) * safeScreenScale,
                    (texture.height + 10.0f) * safeScreenScale},
          3.0f, WHITE);
    }
  }
  void unloadObjectTexture() override { UnloadTexture(sharedTexture); }

  bool isBatteryConnected();
};

#endif
