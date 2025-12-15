#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable{
private:
    vec3 center;
    double radius;
public:
    sphere(const vec3& center, double radius) : center(center), radius(radius) {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override{
        vec3 oc = r.getOrigin() - center;
        double b = 2.0*dot(r.getDirection(), oc);
        double a = dot(r.getDirection(), r.getDirection());
        double c = dot(oc, oc) - radius * radius;
        double det = b*b - 4*a*c;

        if(det < 0.0) return false;

        double root = (-b - sqrt(det))/(2*a);
        if(!ray_t.contains(root)){
            root = (-b + sqrt(det))/(2*a);
            if(!ray_t.contains(root)){
                return false;
            }
        }

        rec.t = root;
        rec.point = r.at(root);
        vec3 out_normal = (rec.point - center) / radius;
        rec.set_face_normal(r, out_normal);

        return true;
    }
};