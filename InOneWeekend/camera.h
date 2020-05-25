#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "vec3.h"

class Camera {
public:
  Camera() {
    auto aspect_ratio = 16.0 / 9.0;
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focalLength = 1.0;

    origin = Point3(0, 0, 0);
    viewport_x = Vec3(viewport_width, 0.0, 0.0);
    viewport_y = Vec3(0.0, viewport_height, 0.0);
    viewport_LL =
        origin - viewport_x / 2 - viewport_y / 2 - Vec3(0.0, 0.0, focalLength);
  }

  Ray GetRay(double u, double v) const {
    return Ray(origin, viewport_LL + u * viewport_x + v * viewport_y - origin);
  }

private:
  Point3 origin;
  Point3 viewport_LL;
  Vec3 viewport_x;
  Vec3 viewport_y;
};

#endif // CAMERA_H
