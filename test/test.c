#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

typedef struct vec3
{
    double x;
    double y;
    double z;
} t_vec3;

typedef struct sphere
{
    t_vec3  oc;
    double  a;
    double  b;
    double  c;
} t_sphere;

typedef struct ray
{
    t_vec3  origin;
    t_vec3  direction;
} t_ray;


void    write_color(t_vec3 *pixel_color)
{
    double  r;
    double  g;
    double  b;
    int     rbyte;
    int     gbyte;
    int     bbyte;

    r = pixel_color->x;
    g = pixel_color->y;
    b = pixel_color->z;

    rbyte = (int)(255.999 * r);
    gbyte = (int)(255.999 * g);
    bbyte = (int)(255.999 * b);
    printf("%d %d %d\n", rbyte, gbyte, bbyte);

}

bool    hit_sphere(t_vec3 center, double radius, t_ray ray)
{
    t_sphere    sphere;
    double      discriminant;

    sphere.oc = subtrac_vec_vec(center, ray.origin);
    sphere.a = dot_vec(ray.direction, ray.direction);
    sphere.b = -2.0 * dot_vec(ray.direction, sphere.oc);
    sphere.c = dot_vec(sphere.oc, sphere.oc) - (radius * radius);
    discriminant = sphere.b * sphere.b - 4 * sphere.a * sphere.c;
    if (discriminant >= 0)
        return (true);
    return (false);
}

int main()
{
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = (int)(image_width / aspect_ratio);
    int i = 0;
    int j = 0;

    printf("P3\n%d %d\n255\n", image_width, image_height);

    while (j < image_height)
    {
        while (i < image_width)
        {
            t_vec3 pixel_color = hit_sphere(i, j);
            i++;
        }
        i = 0;
        j++;
    }
    return 0;
}