#ifndef HITABLE_H_INCLUDED
#define HITABLE_H_INCLUDED

#include "ray.h"
#include "glm/glm/vec3.hpp"
#include "glm/glm/glm.hpp"

class material;

struct hit_record
{
    float t;
    float u;
    float v;
    glm::vec3 p;
    glm::vec3 normal;
    material *mat_ptr;
};

class hitable
{
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif // HITABLE_H_INCLUDED
