#pragma once

#include <cmath>
#include <iostream>
#include "utils.h"

const double pi = 3.1415926535897932385;

class vec3{
public:
    double e[3];

    vec3() : e{0, 0, 0,} {}
    vec3(double ex, double ey, double ez) : e{ex, ey, ez} {}

    double x() const {return e[0];}
    double y() const {return e[1];}
    double z() const {return e[2];}

    vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
    double operator[](int i) const {return e[i];}
    double& operator[](int i) {return e[i];}

    vec3& operator+=(const vec3& v){
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator *=(double t){
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator /=(double t){
        return *this*=(1/t);
    }

    double length() const {return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);}

    static vec3 random() {
        return vec3(random_double(), random_double(), random_double());
    }

    static vec3 random(double min, double max){
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }
};

inline std::ostream& operator<<(std::ostream& out, const vec3& v){
    return out << v.e[0] << ", " << v.e[1] << ", " << v.e[2] << std::endl;
}

inline vec3 operator+(const vec3& u, const vec3& v){
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v){
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v){
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(const vec3& u, double t){
    return vec3(u.e[0] * t, u.e[1]*t, u.e[2]*t);
}

inline vec3 operator*(double t, const vec3& u){
    return u * t;
}

inline vec3 operator/(const vec3& u, double t){
    return u * (1/t);
}

inline double dot(const vec3& u, const vec3& v){
    return u.e[0]*v.e[0] + u.e[1]*v.e[1] + u.e[2]*v.e[2];
}

inline vec3 cross(const vec3&u, const vec3& v){
    return vec3(u.e[1]*v.e[2] - v.e[1]*u.e[2], v.e[0]*u.e[2] - u.e[0]*v.e[2], u.e[0]*v.e[1] - v.e[0]*u.e[1]);
}

inline vec3 unit_vec(const vec3& u){
    return u*(1/u.length());
}

inline vec3 random_unit_vector(){
    double z = random_double(-1, 1);
    double a = random_double(0, 2*pi);
    double r = sqrt(1 - z*z);

    double x = r * cos(a);
    double y = r * sin(a);

    if((x*x + y*y + z*z) < 1e-40) return vec3(1, 0, 0);
    else return vec3(x, y, z);
}

inline vec3 random_on_surface(const vec3& norm){
    vec3 on_sphere = random_unit_vector();
    if(dot(on_sphere, norm) > 0.0) return on_sphere;
    else -on_sphere;
}
