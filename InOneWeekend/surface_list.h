#ifndef SURFACELIST_H
#define SURFACELIST_H

#include "ray.h"
#include "surface.h"

#include <memory>
#include <vector>

class SurfaceList : public Surface {
public:
  SurfaceList() {}
  SurfaceList(std::shared_ptr<Surface> surface) { Add(surface); }

  void Clear() { surfaces.clear(); }
  void Add(std::shared_ptr<Surface> surface) { surfaces.push_back(surface); }

  virtual bool Hit(const Ray &r, double t_min, double t_max,
                   HitRecord &rec) const;

private:
  std::vector<std::shared_ptr<Surface>> surfaces;
};

bool SurfaceList::Hit(const Ray &r, double t_min, double t_max,
                      HitRecord &rec) const {
  HitRecord temp;
  bool hit = false;
  auto nearest = t_max;

  for (const auto &surface : surfaces) {
    if (surface->Hit(r, t_min, nearest, temp)) {
      hit = true;
      nearest = temp.t;
      rec = temp;
    }
  }

  return hit;
}

#endif // SURFACELIST_H
