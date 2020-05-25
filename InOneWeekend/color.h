#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

void WriteColor(std::ostream &out, Color3 pixel_color, int samples_per_pixel) {
  auto r = pixel_color.R();
  auto g = pixel_color.G();
  auto b = pixel_color.B();

  // Divide by number of samples.
  auto scale = 1.0 / samples_per_pixel;
  r = sqrt(scale * r);
  g = sqrt(scale * g);
  b = sqrt(scale * b);

  // Write the translated [0,255] value of each color component.
  out << static_cast<int>(255.999 * Clamp(r, 0.0, 0.999)) << ' '
      << static_cast<int>(255.999 * Clamp(g, 0.0, 0.999)) << ' '
      << static_cast<int>(255.999 * Clamp(b, 0.0, 0.999)) << '\n';
}

void WriteColor(std::ostream &out, Color3 pixel_color) {
  // Write the translated [0,255] value of each color component.
  out << static_cast<int>(255.999 * pixel_color.X()) << ' '
      << static_cast<int>(255.999 * pixel_color.Y()) << ' '
      << static_cast<int>(255.999 * pixel_color.Z()) << '\n';
}

#endif
