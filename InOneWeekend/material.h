#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "surface.h"
#include "vec3.h"

class Material {
public:
  virtual bool Scatter(const Ray &r_in, const HitRecord &rec,
                       Color3 &attenuation, Ray &scattered) const = 0;
};

#endif // MATERIAL_H
