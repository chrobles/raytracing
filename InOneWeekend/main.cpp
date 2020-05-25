#include "common.h"

#include "camera.h"
#include "color.h"
#include "lambertian.h"
#include "metal.h"
#include "sphere.h"
#include "surface_list.h"
#include "vec3.h"
#include <iostream>

Color3 RayColor(const Ray &r, const Surface &world, int depth) {
  HitRecord rec;

  if (depth <= 0)
    return Color3(0, 0, 0);

  if (world.Hit(r, 0.001, infinity, rec)) {
    Ray scattered;
    Color3 attenuation;
    if (rec.mat_ptr->Scatter(r, rec, attenuation, scattered))
      return attenuation * RayColor(scattered, world, depth - 1);
    return Color3(0, 0, 0);

    Point3 target = rec.p + rec.normal + RandomUnitVector();
    return 0.5 * RayColor(Ray(rec.p, target - rec.p), world, depth - 1);
  }

  Vec3 direction = UnitVector(r.Endpoint());
  auto t = 0.5 * (direction.Y() + 1.0);
  return (1.0 - t) * Color3(1.0, 1.0, 1.0) + t * Color3(0.5, 0.7, 1.0);
}

int main() {
  // Image dimensions
  const double aspect_ratio = 16.0 / 9.0;

  const int imageWidth = 384;
  const int imageHeight = static_cast<int>(imageWidth / aspect_ratio);

  const int samples_per_pixel = 100;
  const int maxDepth = 3;

  std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

  Camera cam;

  SurfaceList world;
  world.Add(std::make_shared<Sphere>(
      Point3(0, 0, -1), 0.5,
      std::make_shared<Lambertian>(Color3(0.7, 0.3, 0.3))));
  world.Add(std::make_shared<Sphere>(
      Point3(0, -100.5, -1), 100,
      std::make_shared<Lambertian>(Color3(0.8, 0.8, 0.0))));

  world.Add(std::make_shared<Sphere>(
      Point3(1, 0, -1), 0.5, std::make_shared<Metal>(Color3(0.8, 0.6, 0.2))));
  world.Add(std::make_shared<Sphere>(
      Point3(-1, 0, -1), 0.5, std::make_shared<Metal>(Color3(0.8, 0.8, 0.8))));

  for (int j = imageHeight - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < imageWidth; ++i) {
      Color3 pixel_color(0.0, 0.0, 0.0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + RandomDouble()) / (imageWidth - 1);
        auto v = (j + RandomDouble()) / (imageHeight - 1);
        Ray r = cam.GetRay(u, v);
        pixel_color += RayColor(r, world, maxDepth);
      }
      WriteColor(std::cout, pixel_color, samples_per_pixel);
    }
  }
  std::cerr << "\nDone.\n";
}
