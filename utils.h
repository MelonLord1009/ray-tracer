#pragma once
#include <random>

inline double random_double(){
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    static std::mt19937 randgen;
    return dist(randgen);
}

inline double random_double(double min, double max){
    return min + (max - min) * random_double();
}   