#ifndef WIRE_HPP
#define WIRE_HPP

#include "../../movable_object.hpp"
#include "raylib.h"
#include "raymath.h"
#include <memory>

struct Wire {
  std::shared_ptr<MovableObject> from;
  std::shared_ptr<MovableObject> to;
  bool fromPositive;
  bool toPositive;

  Wire(std::shared_ptr<MovableObject> f, std::shared_ptr<MovableObject> t,
       bool fPos, bool tPos)
      : from(f), to(t), fromPositive(fPos), toPositive(tPos) {}

  void draw() const {
    if (from && to) {
      Vector2 start = fromPositive ? from->getPositivePinPosition()
                                   : from->getNegativePinPosition();
      Vector2 end = toPositive ? to->getPositivePinPosition()
                               : to->getNegativePinPosition();

      DrawLineEx(start, end, 6.0f, BLACK); // outline
      DrawLineEx(start, end, 4.0f, RED);   // inner wire
    }
  }
};

#endif
