#include "Common.h"

#include "Sphere.h"
#include "SurfaceList.h"

#include <iostream>

Color3 RayColor(const Ray &r, const Surface &world) {
  HitRecord rec;
  if (world.Hit(r, 0, infinity, rec)) {
    return 0.5 * (rec.normal + Color3(1, 1, 1));
  }
  Vec3 direction = UnitVector(r.Endpoint());
  auto t = 0.5 * (direction.Y() + 1.0);
  return (1.0 - t) * Color3(1.0, 1.0, 1.0) + t * Color3(0.5, 0.7, 1.0);
}

int main() {
  // Image dimensions
  const double aspectRatio = 2.0 / 1.0;

  const int imageWidth = 800;
  const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

  std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

  // Viewport dimensions
  const double viewportWidth = 4.0;
  const double viewportHeight = viewportWidth / aspectRatio;
  const double focalLength = 1.0;

  // Coordinate origin
  const Point3 origin = Point3(0, 0, 0);

  // Viewport coordinates
  const Vec3 viewportX = Vec3(viewportWidth, 0, 0);
  const Vec3 viewportY = Vec3(0, viewportHeight, 0);
  const Point3 viewportLL =
      origin - viewportX / 2 - viewportY / 2 - Vec3(0, 0, focalLength);

  SurfaceList world;
  world.Add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
  world.Add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

  for (int j = imageHeight - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < imageWidth; ++i) {
      double u = double(i) / (imageWidth - 1);
      double v = double(j) / (imageHeight - 1);

      Ray r(origin, viewportLL + u * viewportX + v * viewportY - origin);
      Color3 pixelColor = RayColor(r, world);
      WriteColor(std::cout, pixelColor);
    }
  }
  std::cerr << "\nDone.\n";
}
