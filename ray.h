#pragma once
#include "vec3.h"

class ray{
private:
    vec3 orig;
    vec3 dir;
public:
    ray() {}
    ray(const vec3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    const vec3& getOrigin() const {return orig;}
    const vec3& getDirection() const {return dir;}

    vec3 at(double t) const{
        return orig + dir * t;
    }
};