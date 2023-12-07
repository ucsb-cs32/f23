#ifndef VEC2_H
#define VEC2_H

#include <cstdlib>

struct Vec2 {
  float x;
  float y;

  Vec2() {}
  Vec2(float x, float y): x(x), y(y) {}

  void randomize() {
    x = 2.0f * float(rand()) / RAND_MAX - 1.0f;
    y = 2.0f * float(rand()) / RAND_MAX - 1.0f;
  }

  Vec2& operator += (const Vec2& other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vec2& operator -= (const Vec2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  Vec2& operator *= (float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  Vec2 operator - (const Vec2& other) {
    return Vec2(x - other.x, y - other.y);
  }

  Vec2 operator * (float scalar) {
    return Vec2(x * scalar, y * scalar);
  }
};

#endif
