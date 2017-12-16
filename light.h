#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#include "material.h"
#include "texture.h"

class diffuse_light : public material
{
public:
    diffuse_light(texture *a) : emit(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, glm::vec3& attenuation, ray& scattered) const
    {
        return false;
    }
    virtual glm::vec3 emitted(float u, float v, const glm::vec3& p) const
    {
        return emit->value(u,v,p);
    }

    texture *emit;
};

#endif // LIGHT_H_INCLUDED
