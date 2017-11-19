#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "ray.h"
#include "hitable.h"

struct hit_record;

bool refract(const glm::vec3& v, const glm::vec3& n, float ni_over_nt, glm::vec3& refracted) {
    glm::vec3 uv = glm::normalize(v);
    //float dt = glm::dot(uv, n);
    //float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
    glm::vec3 test = glm::refract(uv, n, ni_over_nt);
    if (test == glm::vec3(0.0,0.0,0.0)) {
        //refracted = (float)ni_over_nt*(uv - n*(float)dt) - n*(float)sqrt(discriminant);
        return false;
    }
    else
        refracted = test;
        return true;
}

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
        metal(const glm::vec3& a, float f) : albedo(a) {if(f<1) fuzz = f; else fuzz = 1;}
        virtual bool scatter(const ray& r_in, const hit_record& rec, glm::vec3& attenuation, ray& scattered) const  {
            glm::vec3 reflected = glm::reflect(glm::normalize(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
            attenuation = albedo;
            return (glm::dot(scattered.direction(), rec.normal) > 0);
        }
        glm::vec3 albedo;
        float fuzz;
};

class dielectric : public material {
    public:
        dielectric(float ri) : ref_idx(ri) {}

        virtual bool scatter(const ray& r_in, const hit_record& rec, glm::vec3& attenuation, ray& scattered) const  {
             glm::vec3 outward_normal;
             glm::vec3 reflected = reflect(r_in.direction(), rec.normal);
             float ni_over_nt;
             attenuation = glm::vec3(1.0, 1.0, 1.0);
             glm::vec3 refracted;

             if (glm::dot(r_in.direction(), rec.normal) > 0) {
                  outward_normal = -rec.normal;
                  ni_over_nt = ref_idx;
             }
             else {
                  outward_normal = rec.normal;
                  ni_over_nt = 1.0 / ref_idx;

             }
             if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
                {scattered = ray(rec.p, refracted);}
             else{
                scattered = ray(rec.p, reflected);
                return false;
             }
             return true;
        }

        float ref_idx;
};

#endif // MATERIAL_H_INCLUDED
