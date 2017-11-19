#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "ray.h"
#include "hitable.h"

struct hit_record;

glm::vec3 random_in_unit_sphere()
{
    glm::vec3 p;

    do
    {
        p = 2.0f*glm::vec3((float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX) - glm::vec3(1.0, 1.0, 1.0);
    } while((glm::length(p)*glm::length(p)) >= 1.0f);
    return p;
}

class material  {
    public:
        virtual bool scatter(const ray& r_in, const hit_record& rec, glm::vec3& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
    public:
        lambertian(const glm::vec3& a) : albedo(a) {}
        virtual bool scatter(const ray& r_in, const hit_record& rec, glm::vec3& attenuation, ray& scattered) const  {
             glm::vec3 target = rec.p + rec.normal + random_in_unit_sphere();
             scattered = ray(rec.p, target-rec.p);
             attenuation = albedo;
             return true;
        }

        glm::vec3 albedo;
};

class metal : public material {
    public:
        metal(const glm::vec3& a) : albedo(a) {}
        virtual bool scatter(const ray& r_in, const hit_record& rec, glm::vec3& attenuation, ray& scattered) const  {
            glm::vec3 reflected = glm::reflect(glm::normalize(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return (glm::dot(scattered.direction(), rec.normal) > 0);
        }
        glm::vec3 albedo;
};

#endif // MATERIAL_H_INCLUDED
