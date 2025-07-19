#ifndef MOVABLE_OBJECT_HPP
#define MOVABLE_OBJECT_HPP

#include "raylib.h"

struct MovableObject {
  Vector2 position;
  float rotation;
  bool isActive = false;
  Texture2D texture;

  MovableObject(Vector2 pos = {0, 0}, float rotate = 0.0f)
      : position(pos), rotation(rotate) {}

  virtual void loadObjectTexture() = 0;
  virtual void update() = 0;
  virtual void draw() = 0;
  virtual void unloadObjectTexture() = 0;

  virtual Rectangle getCollider() const = 0;
  virtual Rectangle getPositiveCollider() const { return {}; }
  virtual Rectangle getNegativeCollider() const { return {}; }

  virtual Vector2 getPositivePinPosition() const {
    Rectangle pos = getPositiveCollider();
    return {pos.x + pos.width / 2, pos.y + pos.height / 2};
  }

  virtual Vector2 getNegativePinPosition() const {
    Rectangle neg = getNegativeCollider();
    return {neg.x + neg.width / 2, neg.y + neg.height / 2};
  }

  virtual ~MovableObject() = default;
};

#endif
