#include "vec3.h"

vec3::vec3() : v{0,0,0} {};
vec3::vec3(double x, double y, double z) : v{x,y,z} {};

vec3 vec3::operator-() const {
    return {-v[0], -v[1], -v[2]};
}