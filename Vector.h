#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include "Utillities.h"
#include <float.h>

class  Vector{
  public:
    double coor[3];

    Vector() : coor{0,0,0} {}
    Vector(double co0, double co1, double co2) : coor{co0, co1, co2} {}

    double getX() const { return coor[0]; }
    double getY() const { return coor[1]; }
    double getZ() const { return coor[2]; }

    Vector operator-() const { return Vector(-coor[0], -coor[1], -coor[2]); }
    double operator[](int i) const { return coor[i]; }
    double& operator[](int i) { return coor[i]; }

    Vector& operator+=(const Vector& v) {
        coor[0] += v.coor[0];
        coor[1] += v.coor[1];
        coor[2] += v.coor[2];
        return *this;
    }

    Vector& operator*=(double t) {
        coor[0] *= t;
        coor[1] *= t;
        coor[2] *= t;
        return *this;
    }

    Vector& operator/=(double t) {
        return *this *= 1/t;
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return coor[0]*coor[0] + coor[1]*coor[1] + coor[2]*coor[2];
    }
    static Vector random() {
            return Vector(random_double(), random_double(), random_double());
        }

    static Vector random(double min, double max) {
            return Vector(random_double(min,max), random_double(min,max), random_double(min,max));
        }
};
inline std::ostream& operator<<(std::ostream& out, const Vector& v) {
    return out << v.coor[0] << ' ' << v.coor[1] << ' ' << v.coor[2];
}

inline Vector operator+(const Vector& u, const Vector& v) {
    return Vector(u.coor[0] + v.coor[0], u.coor[1] + v.coor[1], u.coor[2] + v.coor[2]);
}

inline Vector operator-(const Vector& u, const Vector& v) {
    return Vector(u.coor[0] - v.coor[0], u.coor[1] - v.coor[1], u.coor[2] - v.coor[2]);
}

inline Vector operator*(const Vector& u, const Vector& v) {
    return Vector(u.coor[0] * v.coor[0], u.coor[1] * v.coor[1], u.coor[2] * v.coor[2]);
}

inline Vector operator*(double t, const Vector& v) {
    return Vector(t*v.coor[0], t*v.coor[1], t*v.coor[2]);
}

inline Vector operator*(const Vector& v, double t) {
    return t * v;
}

inline Vector operator/(const Vector& v, double t) {
    return (1/t) * v;
}

inline double dot(const Vector& u, const Vector& v) {
    return u.coor[0] * v.coor[0]
         + u.coor[1] * v.coor[1]
         + u.coor[2] * v.coor[2];
}

inline Vector cross(const Vector& u, const Vector& v) {
    return Vector(u.coor[1] * v.coor[2] - u.coor[2] * v.coor[1],
                u.coor[2] * v.coor[0] - u.coor[0] * v.coor[2],
                u.coor[0] * v.coor[1] - u.coor[1] * v.coor[0]);
}

inline Vector unit_vector(const Vector& v) {
    return v / v.length();
}
inline void write_color(std::ostream& out, const Vector& pixel_color) {
    auto x = pixel_color.getX();
    auto y = pixel_color.getY();
    auto z = pixel_color.getZ();
    auto r = x > 1 ? 1: x;
    auto g = y > 1 ? 1: y;
    auto b = z > 1 ? 1: z;

    r = sqrt(r);
    g = sqrt(g);
    b = sqrt(b);

    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
#endif
