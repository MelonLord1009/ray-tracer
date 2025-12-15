#pragma once

#include "hittable.h"
#include "color.h"
#include "utils.h"

#include <random>



class camera{
public:
    double aspect_ratio = 1.0;
    int imw = 100;
    int samples_pp = 10;
    int max_ref = 10;

    void render(const hittable& world){
        initialize();    

        std::cout << "P3\n" << imw << " " << imh << "\n255\n";
        for(int j = 0 ; j < imh ; j++){
            std::clog << "Scanlines remaining\n" << imh - j << std::endl; 
            for(int i = 0 ; i < imw ; i++){
                vec3 pix_col(0.0, 0.0, 0.0);
                //anti-aliasing
                for(int sample = 0 ; sample < samples_pp ; sample++){
                    ray r = get_ray(i, j);
                    pix_col += ray_color(r, world, max_ref);
                }
                write_color(std::cout, pix_col*pixel_samples_scale);
            }
        }
        std::clog << "Done.           \n" << std::endl;

    }

private:
    int imh;
    vec3 camera_center;
    vec3 zzpix_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    double pixel_samples_scale;

    void initialize(){
        imh = int(imw/aspect_ratio);
        imh = (imh < 1) ? 1 : imh;
        pixel_samples_scale = 1.0 / samples_pp;
        double focal_length = 1.0;
        double viewport_height = 2.0;
        double viewport_width = viewport_height * (double(imw)/imh);
        camera_center = vec3(0, 0, 0);

        vec3 viewport_u = vec3(viewport_width, 0, 0);
        vec3 viewport_v = vec3(0, -viewport_height, 0);

        pixel_delta_u = viewport_u/imw;
        pixel_delta_v = viewport_v/imh;

        vec3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - (viewport_u/2) - (viewport_v/2);
        zzpix_loc = viewport_upper_left + 0.5*(pixel_delta_u + pixel_delta_v);
    }

    vec3 sample_square() const{
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    ray get_ray(int i, int j) const{
        vec3 offset = sample_square();
        vec3 pixel_sample = zzpix_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);
        vec3 ray_dir = pixel_sample - camera_center;
        return ray(camera_center, ray_dir); 
    }

    vec3 ray_color(const ray& r, const hittable& world, int depth) const{
        if(depth < 0) return vec3(0, 0, 0);
        hit_record rec;
        if(world.hit(r, interval(0.001, infinity) , rec)){
            vec3 dir = rec.normal + random_unit_vector();
            return 0.5 * ray_color(ray(rec.point, dir), world, depth - 1);
        }
        vec3 unit_dir = unit_vec(r.getDirection());
        double alpha = 0.5 * (unit_dir.y() + 1.0);
        return (1.0 - alpha) * vec3(1.0, 1.0, 1.0) + alpha * vec3(0.5, 0.7, 1.0);
    }
};