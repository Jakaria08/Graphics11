#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include "glm/glm/vec3.hpp"
#include "glm/glm/glm.hpp"
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "material.h"

using namespace std;

float random_value()
{
  float r = drand48();

  return r;
}


glm::vec3 color(const ray& r, hitable *world, int depth)
{
    hit_record rec;

    if(world->hit(r, 0.001, FLT_MAX, rec))
    {
        ray scattered;
        glm::vec3 attenuation;

        if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation*color(scattered, world, depth+1);
        }
        else
        {
            return glm::vec3(0,0,0);
        }
    }

    else
    {
        glm::vec3 unit_direction = glm::normalize(r.direction());
        float t = 0.5f*(unit_direction.y + 1.0f);
        return (1.0f-t)*glm::vec3(1.0, 1.0, 1.0) + t*glm::vec3(0.5, 0.7, 1.0);
    }
}

int main()
{
    freopen("output.ppm","w",stdout);

    int nx = 200;
    int ny = 100;
    int ns = 100;

    cout << "P3\n" << nx << " " << ny << "\n255\n";

    hitable *list[4];

    list[0] = new sphere(glm::vec3(0,0,-1), 0.5, new lambertian(glm::vec3(0.8, 0.3, 0.3)));
    list[1] = new sphere(glm::vec3(0,-100.5,-1), 100, new lambertian(glm::vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(glm::vec3(1,0,-1), 0.5, new metal(glm::vec3(0.8, 0.6, 0.2), 0.3));
    list[3] = new sphere(glm::vec3(-1,0,-1), 0.5, new dielectric(1.5));

    hitable *world = new hitable_list(list,4);
    camera cam;


    for (int j = ny - 1; j >=0; j--)
    {
        for(int  i = 0; i < nx; i++)
        {
            glm::vec3 col(0,0,0);
            for(int k=0; k<ns; k++)
            {
                float u = float(i + random_value())/float(nx);
                float v = float(j + random_value())/float(ny);

                ray r = cam.get_ray(u,v);
                //glm::vec3 p = r.point_at_parameter(2.0);
                col += color(r,world,0);
            }
            col /= float(ns);
            col = glm::vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            cout << ir << " " << ig << " " << ib << "\n";
        }
        //cout << "Image Pixel Row " << 100-j <<"...........................................";
    }
    return 0;
}
