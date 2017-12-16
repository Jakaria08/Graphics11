#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED

#include "hitable.h"
#include "glm/glm/vec3.hpp"
#include "glm/glm/glm.hpp"
#include "texture.h"
#include "light.h"

class sphere: public hitable
{
public:
    sphere() {}
    sphere(glm::vec3 cen0, glm::vec3 cen1, float t0, float t1, float r, material *m) :
         center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), mat_ptr(m)  {};

    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
    glm::vec3 center(float time) const;
    glm::vec3 center0, center1;
    float time0, time1;
    float radius;
    material *mat_ptr;
};

glm::vec3 sphere::center(float time) const
{
    return center0 + ((time - time0) / (time1-time0))*(center1-center0);
}

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
    glm::vec3 oc = r.origin() - center(r.time());
    float a = glm::dot(r.direction(), r.direction());
    float b = glm::dot(oc, r.direction());
    float c = glm::dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0)
    {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center(r.time())) / radius;
             rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center(r.time())) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}


#endif // SPHERE_H_INCLUDED
