#include <cmath>
#include "vec3.h"

vec3::vec3() : v{0,0,0} {};
vec3::vec3(double x, double y, double z) : v{x,y,z} {};

double vec3::x() const {
    return v[0];
}

double vec3::y() const {
    return v[1];
}

double vec3::z() const {
    return v[2];
}

vec3 vec3::operator-() const {
    return {-v[0], -v[1], -v[2]};
}

vec3& vec3::operator+=(const vec3& w) {
    v[0] += w.v[0];
    v[1] += w.v[1];
    v[2] += w.v[2];
    return *this;
}

vec3& vec3::operator*=(double t) {
    v[0] *= t;
    v[1] *= t;
    v[2] *= t;
    return *this;
}

vec3& vec3::operator/=(double t) {
    return *this *= (1/t);
}

double vec3::operator[](int i) const {
    return v[i];
}

double& vec3::operator[](int i) {
    return v[i];
}

double vec3::length() const {
    return sqrt(length_squared());
}

double vec3::length_squared() const {
    return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
}


vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.x(), t*v.y(), t*v.z());
}

vec3 operator*(const vec3& v, double t) {
    return t * v;
}

vec3 operator*(const vec3& v, const vec3& w) {
    return vec3(v.x()*w.x(), v.y()*w.y(), v.z()*w.z());
}

vec3 operator+(const vec3& v, const vec3& w) {
    return vec3(v.x()+w.x(), v.y()+w.y(), v.z()+w.z());
}

vec3 operator-(const vec3& v, const vec3& w) {
    return vec3(v.x()-w.x(), v.y()-w.y(), v.z()-w.z());
}

vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

// Algebraic definition of cross product: v X w = (v2w3 + v3w2)i + (v3w1 - v1w3)j + (v1w2 - v2w1)k
vec3 cross(const vec3& v, const vec3& w) {
    return vec3(v.y()*w.z()+v.z()*w.y(), v.z()*w.x()-v.x()*w.z(), v.x()*w.y()-v.y()*w.x());
}

vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

double dot(const vec3& v, const vec3& w) {
    return v.x()*w.x() + v.y()*w.y() + v.z()*w.z();
}

