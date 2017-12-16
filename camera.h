#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "ray.h"
#include "glm/glm/vec3.hpp"
#include "glm/glm/glm.hpp"
#include <math.h>

glm::vec3 random_in_unit_disk() {
    glm::vec3 p;
    do {
        p = float(2.0)*glm::vec3(drand48(),drand48(),0) - glm::vec3(1,1,0);
    } while (glm::dot(p,p) >= 1.0);
    return p;
}

class camera
{
public:
    camera(glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup,float vfov, float aspect, float aperture, float focus_dist, float t0, float t1)
    {
        time0 = t0;
        time1 = t1;
        lens_radius = aperture/2;
        float theta = vfov*M_PI/180;
        float half_height = tan(theta/2);
        float half_width = aspect * half_height;

        origin = lookfrom;
        w = glm::normalize(lookfrom - lookat);
        u = glm::normalize(cross(vup, w));
        v = glm::cross(w, u);

        lower_left_corner = origin  - half_width*focus_dist*u -half_height*focus_dist*v - focus_dist*w;
        horizontal = 2*half_width*focus_dist*u;
        vertical = 2*half_height*focus_dist*v;

    }

    ray get_ray(float s, float t)
    {
        glm::vec3 rd = lens_radius*random_in_unit_disk();
        glm::vec3 offset = u * rd.x + v * rd.y;
        float time = time0 + drand48()*(time1-time0);
        return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset,time);
    }

    glm::vec3 lower_left_corner;
    glm::vec3 horizontal;
    glm::vec3 vertical;
    glm::vec3 origin;

    glm::vec3 u, v, w;
    float time0, time1;
    float lens_radius;
};

#endif // CAMERA_H_INCLUDED
