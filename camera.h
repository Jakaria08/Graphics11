#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "ray.h"
#include "glm/glm/vec3.hpp"
#include "glm/glm/glm.hpp"

class camera
{
public:
    camera(float vfov, float aspect)
    {
        float theta = vfov*M_PI/180;
        float half_height = tan(theta/2);
        float half_width = aspect * half_height;

        lower_left_corner = glm::vec3(-half_width, -half_height, -1.0);
        horizontal = glm::vec3(2.0*half_width, 0.0, 0.0);
        vertical = glm::vec3(0.0, 2.0*half_height, 0.0);
        origin = glm::vec3(0.0, 0.0, 0.0);
    }

    ray get_ray(float u, float v)
    {
        return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    }

    glm::vec3 lower_left_corner;
    glm::vec3 horizontal;
    glm::vec3 vertical;
    glm::vec3 origin;
};

#endif // CAMERA_H_INCLUDED
