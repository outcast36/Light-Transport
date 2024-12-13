#include <cmath>
#include "vec3.h"

template <typename T> vec3<T>::vec3() : v{0,0,0} {};
template <typename T> vec3<T>::vec3(T x, T y, T z) : v{x,y,z} {};

template <typename T> T vec3<T>::x() const {
    return v[0];
}

template <typename T> T vec3<T>::y() const {
    return v[1];
}

template <typename T> T vec3<T>::z() const {
    return v[2];
}

template <typename T> vec3<T> vec3<T>::operator-() const {
    return {-v[0], -v[1], -v[2]};
}

template <typename T> vec3<T>& vec3<T>::operator+=(const vec3<T>& w) {
    v[0] += w.v[0];
    v[1] += w.v[1];
    v[2] += w.v[2];
    return *this;
}

template <typename T> vec3<T>& vec3<T>::operator*=(T t) {
    v[0] *= t;
    v[1] *= t;
    v[2] *= t;
    return *this;
}

template <typename T> vec3<T>& vec3<T>::operator/=(T t) {
    return *this *= (1/t);
}

template <typename T> T vec3<T>::operator[](int i) const {
    return v[i];
}

template <typename T> T& vec3<T>::operator[](int i) {
    return v[i];
}

template <typename T> T vec3<T>::length() const {
    return sqrt(length_squared());
}

template <typename T> T vec3<T>::length_squared() const {
    return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
}


template <typename T> vec3<T> operator*(T t, const vec3<T>& v) {
    return vec3<T>(t*v.x(), t*v.y(), t*v.z());
}

template <typename T> vec3<T> operator*(const vec3<T>& v, T t) {
    return t * v;
}

template <typename T> vec3<T> operator*(const vec3<T>& v, const vec3<T>& w) {
    return vec3<T>(v.x()*w.x(), v.y()*w.y(), v.z()*w.z());
}

template <typename T> vec3<T> operator+(const vec3<T>& v, const vec3<T>& w) {
    return vec3<T>(v.x()+w.x(), v.y()+w.y(), v.z()+w.z());
}

template <typename T> vec3<T> operator-(const vec3<T>& v, const vec3<T>& w) {
    return vec3<T>(v.x()-w.x(), v.y()-w.y(), v.z()-w.z());
}

template <typename T> vec3<T> operator/(const vec3<T>& v, T t) {
    return (1/t) * v;
}

// Algebraic definition of cross product: v X w = (v2w3 + v3w2)i + (v3w1 - v1w3)j + (v1w2 - v2w1)k
template <typename T> vec3<T> cross(const vec3<T>& v, const vec3<T>& w) {
    return vec3<T>(v.y()*w.z()+v.z()*w.y(), v.z()*w.x()-v.x()*w.z(), v.x()*w.y()-v.y()*w.x());
}

template <typename T> vec3<T> unit_vector(const vec3<T>& v) {
    return v / v.length();
}

template <typename T> T dot(const vec3<T>& v, const vec3<T>& w) {
    return v.x()*w.x() + v.y()*w.y() + v.z()*w.z();
}

