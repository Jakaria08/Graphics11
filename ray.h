#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED

#include "glm/glm/vec3.hpp"
#include "glm/glm/glm.hpp"

class ray
{
public:
    glm::vec3 A;
    glm::vec3 B;
    float timev;
    ray() {}
    ray(const glm::vec3& a, const glm::vec3& b, float t = 0.0)
    {
        A = a;
        B = b;
        timev = t;
    }
    glm::vec3 origin() const
    {
        return A;
    }
    glm::vec3 direction() const
    {
        return B;
    }
    glm::vec3 point_at_parameter(float t) const
    {
        return A + t*B;
    }
    float time() const
    {
        return timev;
    }
};

#endif // RAY_H_INCLUDED
