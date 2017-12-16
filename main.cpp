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
#include "texture.h"
#include "light.h"

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
        glm::vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

        if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return emitted+attenuation*color(scattered, world, depth+1);
        }
        else
        {
            return emitted;
        }
    }

    else
    {
        return glm::vec3(0,0,0);
    }
}

hitable *random_scene() {
    int n = 500;
    hitable **list = new hitable*[n+1];
    texture *checker = new checker_texture(new constant_texture(glm::vec3(0.0,0.0,0.0)), new constant_texture(glm::vec3(1.0,1.0,1.0)));
    list[0] =  new sphere(glm::vec3(0,-1000,0), glm::vec3(0,-1000,0),  0.0, 1.0, 1000,new lambertian(checker));
    int i = 1;
    for (int a = -3; a < 3; a++) {
        for (int b = -2; b < 2; b++) {
            float choose_mat = drand48();
            glm::vec3 center(a+0.9*drand48(),0.2,b+0.9*drand48());
            if (glm::length(center-glm::vec3(4,0.2,0)) > 0.9) {
                if (choose_mat < 0.8) {  // diffuse
                    list[i++] = new sphere(center, center+glm::vec3(0,0.5*drand48(),0), 0.0, 1.0,0.2 , new lambertian(new constant_texture(glm::vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48()))));
                }
                else if (choose_mat < 0.95) { // metal
                    list[i++] = new sphere(center, center, 0.0, 1.0, 0.2,
                            new metal(glm::vec3(0.5*(1 + drand48()), 0.5*(1 + drand48()), 0.5*(1 + drand48())),  0.5*drand48()));
                }
                else {  // glass
                    list[i++] = new sphere(center, center,  0.0, 1.0, 0.2 , new dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new sphere(glm::vec3(0, 1, 0), glm::vec3(0, 1, 0),  0.0, 1.0,1.0, new dielectric(1.5));
    list[i++] = new sphere(glm::vec3(-3, 1, 0), glm::vec3(-3, 1, 0),  0.0, 1.0, 1.0, new lambertian(new constant_texture(glm::vec3(0.4, 0.2, 0.1))));
    list[i++] = new sphere(glm::vec3(3, 1, 0), glm::vec3(3, 1, 0), 0.0, 1.0, 1.0, new metal(glm::vec3(0.7, 0.6, 0.5), 0.0));
    list[i++] = new sphere(glm::vec3(0,7,0), glm::vec3(0,7,0), 0.0, 1.0, 2.0, new diffuse_light(new constant_texture(glm::vec3(4,4,4))));
    return new hitable_list(list,i);
}

int main()
{


    int nx = 200;
    int ny = 100;
    int ns = 200;

    cout<< "Creating Image................\n";

    freopen("output.ppm","w",stdout);

    cout << "P3\n" << nx << " " << ny << "\n255\n";

    hitable *list[11];

    list[0] = new sphere(glm::vec3(0,0,-1), glm::vec3(0,0,-1),  0.0, 1.0, 0.5, new lambertian(new constant_texture(glm::vec3(0.1, 0.2, 0.5))));
    list[1] = new sphere(glm::vec3(0,-100.5,-1), glm::vec3(0,-100.5,-1),  0.0, 1.0, 100, new lambertian(new constant_texture(glm::vec3(0.8, 0.8, 0.0))));
    list[2] = new sphere(glm::vec3(1,0,-1), glm::vec3(1,0,-1),  0.0, 1.0, 0.5 , new metal(glm::vec3(0.8, 0.6, 0.2), 0.2));
    list[3] = new sphere(glm::vec3(-1,0,-1), glm::vec3(-1,0,-1),  0.0, 1.0, 0.5 , new dielectric(1.5));
    list[4] = new sphere(glm::vec3(-1,0,-1), glm::vec3(-1,0,-1), 0.0, 1.0, -0.45, new dielectric(1.5)); // -0.45 needed
    list[5] = new sphere(glm::vec3(0, 1, 0), glm::vec3(0, 1, 0),  0.0, 1.0, 1.0,new dielectric(1.5));
    list[6] = new sphere(glm::vec3(-4, 1, 0), glm::vec3(-4, 1, 0),  0.0, 1.0, 1.0 ,new lambertian(new constant_texture(glm::vec3(0.4, 0.2, 0.1))));
    list[7] = new sphere(glm::vec3(4, 1, 0), glm::vec3(4, 1, 0),  0.0, 1.0,1.0, new metal(glm::vec3(0.7, 0.6, 0.5), 0.0));
    list[8] = new sphere(glm::vec3(2, 1, 2), glm::vec3(2, 1, 2),  0.0, 1.0, 0.8, new dielectric(1.5));
    list[9] = new sphere(glm::vec3(5, 0, 2), glm::vec3(5, 0, 2), 0.0, 1.0,  0.5 , new dielectric(1.5));
    list[10] = new sphere(glm::vec3(5, 0, 0), glm::vec3(5, 0, 0),  0.0, 1.0,0.5, new metal(glm::vec3(0.7, 0.6, 0.5), 0.0));

    hitable *world = new hitable_list(list,11);
    world = random_scene();

    glm::vec3 lookfrom(8,4,6);
    glm::vec3 lookat(0,0,0);
    float dist_to_focus = 10;
    float aperture = 0.1;

    camera cam(lookfrom, lookat, glm::vec3(0,1,0), 20, float(nx)/float(ny), aperture, dist_to_focus,0.0,1.0);


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
    fclose(stdout);

    cout<<"Image created.\n";

    return 0;
}
