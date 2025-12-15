#pragma once

#include "vec3.h"
#include "interval.h"

#include<iostream>

inline double gamma(double lin_comp){
    if(lin_comp > 0) return std::sqrt(lin_comp);
    return 0;
}


void write_color(std::ostream& out, const vec3& pix_col){
    
    static const interval intensity(0.000, 0.999);
    double r = pix_col.x();
    double g = pix_col.y();
    double b = pix_col.z();

    r = gamma(r);
    g = gamma(g);
    b = gamma(b);

    double rbyte = int(intensity.clamp(r) * 256);
    double gbyte = int(intensity.clamp(g) * 256);
    double bbyte = int(intensity.clamp(b) * 256);

    out << rbyte << " " << gbyte << " " << bbyte << std::endl;
}
