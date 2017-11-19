#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED

#include "glm/glm/vec3.hpp"
#include "glm/glm/glm.hpp"

class ray
{
public:
    glm::vec3 A;
    glm::vec3 B;
    ray() {}
    ray(const glm::vec3& a, const glm::vec3& b)
    {
        A = a;
        B = b;
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
};

#endif // RAY_H_INCLUDED
