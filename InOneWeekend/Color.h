#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"

#include <iostream>

void WriteColor(std::ostream &out, Color3 pixelColor, int samplesPerPixel) {
  auto r = pixelColor.R();
  auto g = pixelColor.G();
  auto b = pixelColor.B();

  // Divide by number of samples.
  auto scale = 1.0 / samplesPerPixel;
  r *= scale;
  g *= scale;
  b *= scale;

  // Write the translated [0,255] value of each color component.
  out << static_cast<int>(255.999 * Clamp(r, 0.0, 0.999)) << ' '
      << static_cast<int>(255.999 * Clamp(g, 0.0, 0.999)) << ' '
      << static_cast<int>(255.999 * Clamp(b, 0.0, 0.999)) << '\n';
}

void WriteColor(std::ostream &out, Color3 pixelColor) {
  // Write the translated [0,255] value of each color component.
  out << static_cast<int>(255.999 * pixelColor.X()) << ' '
      << static_cast<int>(255.999 * pixelColor.Y()) << ' '
      << static_cast<int>(255.999 * pixelColor.Z()) << '\n';
}

#endif
