#ifndef CAMERA_H
#define CAMERA_H

#include "Common.h"

class Camera {
public:
  Camera() {
    auto aspectRatio = 16.0 / 9.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = aspectRatio * viewportHeight;
    auto focalLength = 1.0;

    origin = Point3(0, 0, 0);
    viewportX = Vec3(viewportWidth, 0.0, 0.0);
    viewportY = Vec3(0.0, viewportHeight, 0.0);
    viewportLL =
        origin - viewportX / 2 - viewportY / 2 - Vec3(0.0, 0.0, focalLength);
  }

  Ray GetRay(double u, double v) const {
    return Ray(origin, viewportLL + u * viewportX + v * viewportY - origin);
  }

private:
  Point3 origin;
  Point3 viewportLL;
  Vec3 viewportX;
  Vec3 viewportY;
};

#endif // CAMERA_H
