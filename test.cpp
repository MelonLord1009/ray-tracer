#include <iostream>
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "hittables.h"
#include "interval.h"
#include "sphere.h"
#include "camera.h"

using std::make_shared;
using std::shared_ptr;

int main(){

    hittables world;
    world.add(make_shared<sphere>(vec3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(vec3(0,-100.5,-1), 100));
    world.add(make_shared<sphere>(vec3(1, -0.3, -1), 0.23));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.imw = 400;
    cam.samples_pp = 100;
    cam.max_ref = 10;

    cam.render(world);
}