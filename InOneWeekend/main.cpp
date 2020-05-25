#include "Common.h"

#include "Camera.h"
#include "Sphere.h"
#include "SurfaceList.h"

#include <iostream>

Color3 RayColor(const Ray &r, const Surface &world, int depth) {
  HitRecord rec;
  if (depth <= 0)
    return Color3(0, 0, 0);
  if (world.Hit(r, 0.001, infinity, rec)) {
    Point3 target = rec.p + rec.normal + RandomUnitVector();
    return 0.5 * RayColor(Ray(rec.p, target - rec.p), world, depth - 1);
  }
  Vec3 direction = UnitVector(r.Endpoint());
  auto t = 0.5 * (direction.Y() + 1.0);
  return (1.0 - t) * Color3(1.0, 1.0, 1.0) + t * Color3(0.5, 0.7, 1.0);
}

int main() {
  // Image dimensions
  const double aspectRatio = 16.0 / 9.0;

  const int imageWidth = 384;
  const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

  const int samplesPerPixel = 100;
  const int maxDepth = 3;

  std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

  Camera cam;

  SurfaceList world;
  world.Add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
  world.Add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

  for (int j = imageHeight - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < imageWidth; ++i) {
      Color3 pixelColor(0.0, 0.0, 0.0);
      for (int s = 0; s < samplesPerPixel; ++s) {
        auto u = (i + RandomDouble()) / (imageWidth - 1);
        auto v = (j + RandomDouble()) / (imageHeight - 1);
        Ray r = cam.GetRay(u, v);
        pixelColor += RayColor(r, world, maxDepth);
      }
      WriteColor(std::cout, pixelColor, samplesPerPixel);
    }
  }
  std::cerr << "\nDone.\n";
}
