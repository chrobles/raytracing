#ifndef VEC3_H
#define VEC3_H

#include "Common.h"

#include <cmath>
#include <iostream>

class Vec3 {
public:
  Vec3() : e{0, 0, 0} {}
  Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  double X() const { return e[0]; }
  double Y() const { return e[1]; }
  double Z() const { return e[2]; }

  double R() const { return e[0]; }
  double G() const { return e[1]; }
  double B() const { return e[2]; }

  Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
  double operator[](int i) const { return e[i]; }
  double &operator[](int i) { return e[i]; }

  Vec3 &operator+=(const Vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  Vec3 &operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  Vec3 &operator/=(const double t) { return *this *= 1 / t; }

  double LengthSquared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  double Length() const { return sqrt(LengthSquared()); }

  inline static Vec3 RandomVec() {
    return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
  }

  inline static Vec3 RandomVec(double min, double max) {
    return Vec3(RandomDouble(min, max), RandomDouble(min, max),
                RandomDouble(min, max));
  }

private:
  double e[3];
};

// Type aliases for Vec3
using Point3 = Vec3; // 3D point
using Color3 = Vec3; // RGB color

// Vec3 Utility Functions

inline std::ostream &operator<<(std::ostream &out, const Vec3 &u) {
  return out << u.X() << ' ' << u.Y() << ' ' << u.Z();
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.X() + v.X(), u.Y() + v.Y(), u.Z() + v.Z());
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.X() - v.X(), u.Y() - v.Y(), u.Z() - v.Z());
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.X() * v.X(), u.Y() * v.Y(), u.Z() * v.Z());
}

inline Vec3 operator*(double t, const Vec3 &u) {
  return Vec3(t * u.X(), t * u.Y(), t * u.Z());
}

inline Vec3 operator*(const Vec3 &u, double t) { return t * u; }

inline Vec3 operator/(Vec3 u, double t) { return (1 / t) * u; }

inline double Dot(const Vec3 &u, const Vec3 &v) {
  return u.X() * v.X() + u.Y() * v.Y() + u.Z() * v.Z();
}

inline Vec3 Cross(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.Y() * v.Z() - u.Z() * v.Y(), u.Z() * v.X() - u.X() * v.Z(),
              u.X() * v.Y() - u.Y() * v.X());
}

inline Vec3 UnitVector(Vec3 v) { return v / v.Length(); }

Vec3 RandomInUnitSphere() {
  while (true) {
    auto p = Vec3::RandomVec(-1, 1);
    if (p.LengthSquared() >= 1)
      continue;
    return p;
  }
}

Vec3 RandomUnitVector() {
  auto a = RandomDouble(0, 2 * pi);
  auto z = RandomDouble(-1, 1);
  auto r = sqrt(1 - z * z);
  return Vec3(r * cos(a), r * sin(a), z);
}

Vec3 Reflect(const Vec3 &v, const Vec3 &n) { return v - 2 * Dot(v, n) * n; }

#endif
