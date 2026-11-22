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
    float coor[3];

    Vector() : coor{0,0,0} {}
    Vector(float co0, float co1, float co2) : coor{co0, co1, co2} {}

    float getX() const { return coor[0]; }
    float getY() const { return coor[1]; }
    float getZ() const { return coor[2]; }

    Vector operator-() const { return Vector(-coor[0], -coor[1], -coor[2]); }
    float operator[](int i) const { return coor[i]; }
    float& operator[](int i) { return coor[i]; }

    Vector& operator+=(const Vector& v) {
        coor[0] += v.coor[0];
        coor[1] += v.coor[1];
        coor[2] += v.coor[2];
        return *this;
    }

    Vector& operator*=(float t) {
        coor[0] *= t;
        coor[1] *= t;
        coor[2] *= t;
        return *this;
    }

    Vector& operator/=(float t) {
        return *this *= 1/t;
    }

    float length() const {
        return std::sqrt(length_squared());
    }

    float length_squared() const {
        return coor[0]*coor[0] + coor[1]*coor[1] + coor[2]*coor[2];
    }
    static Vector random() {
            return Vector(random_float(), random_float(), random_float());
        }

    static Vector random(float min, float max) {
            return Vector(random_float(min,max), random_float(min,max), random_float(min,max));
        }
    bool near_zero() const {
            auto s = 1e-8;
            return (std::fabs(coor[0]) < s) && (std::fabs(coor[1]) < s) && (std::fabs(coor[2]) < s);
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

inline Vector operator*(float t, const Vector& v) {
    return Vector(t*v.coor[0], t*v.coor[1], t*v.coor[2]);
}

inline Vector operator*(const Vector& v, float t) {
    return t * v;
}

inline Vector operator/(const Vector& v, float t) {
    return (1/t) * v;
}

inline float dot(const Vector& u, const Vector& v) {
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
inline Vector reflect(const Vector& v, const Vector& normal){
    return v - 2 * dot(v, normal) * normal;
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
