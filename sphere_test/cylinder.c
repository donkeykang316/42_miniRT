#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    double x, y, z;
} Vector;

typedef struct
{
    Vector origin;
    Vector direction;
} Ray;

typedef struct
{
    Vector base;
    double radius;
    double height;
    Vector direction;
} Cylinder;

typedef struct
{
    int r, g, b;
} Color;

double dot(Vector a, Vector b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector subtract(Vector a, Vector b)
{
    Vector result = {a.x - b.x, a.y - b.y, a.z - b.z};
    return result;
}

// Multiply vector by scalar
Vector multiply(Vector v, double scalar)
{
    Vector result = {v.x * scalar, v.y * scalar, v.z * scalar};
    return result;
}

Vector add(Vector a, Vector b)
{
    Vector result = {a.x + b.x, a.y + b.y, a.z + b.z};
    return result;
}

int intersect_ray_cylinder(Ray ray, Cylinder cylinder, double *t)
{
    Vector d = ray.direction;
    Vector o = ray.origin;
    Vector ca = cylinder.direction;
    Vector oc = subtract(o, cylinder.base);
    
    double cad = dot(ca, d);
    double caoc = dot(ca, oc);
    double card = dot(ca, ca);
    
    double a = dot(d, d) - cad * cad;
    double b = dot(oc, d) - caoc * cad;
    double c = dot(oc, oc) - caoc * caoc - cylinder.radius * cylinder.radius;

    double discriminant = b * b - a * c;
    
    if (discriminant < 0)
        return 0;

    discriminant = sqrt(discriminant);
    
    double t0 = (-b - discriminant) / a;
    double t1 = (-b + discriminant) / a;

    if (t0 > t1)
    {
        double temp = t0;
        t0 = t1;
        t1 = temp;
    }
    double y0 = caoc + t0 * cad;
    double y1 = caoc + t1 * cad;

    if (y0 < 0)
    {
        if (y1 < 0) return 0;
        t0 = t1;
        y0 = y1;
    }
    if (y0 > cylinder.height)
    {
        if (y1 > cylinder.height) return 0;
        t0 = t1;
        y0 = y1;
    }

    *t = t0;
    return 1;
}

void write_ppm(const char *filename, Color *image, int width, int height)
{
    FILE *f = fopen(filename, "w");
    fprintf(f, "P3\n%d %d\n255\n", width, height);
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            Color pixel = image[j * width + i];
            fprintf(f, "%d %d %d ", pixel.r, pixel.g, pixel.b);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

void ray_trace()
{
    const int width = 800;
    const int height = 600;

    Vector camera_pos = {0.0, -3.0, -5.0};
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (double)width / (double)height;
    double focal_length = 1.0;

    Vector horizontal = {viewport_width, 0, 0};
    Vector vertical = {0, viewport_height, 0};
    Vector lower_left_corner = subtract(subtract(subtract(camera_pos, multiply(horizontal, 0.5)), multiply(vertical, 0.5)), (Vector){0, 0, focal_length});

    Color *image = (Color *)malloc(width * height * sizeof(Color));

    Cylinder cylinder =
    {
        .base = {0.0, 0.0, 0.0},
        .radius = 1.0,
        .height = 2.0,
        .direction = {0.0, 1.0, 0.0}
    };

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            double u = (double)i / (double)(width - 1);
            double v = (double)(height - j - 1) / (double)(height - 1);
            Vector direction = add(add(lower_left_corner, multiply(horizontal, u)), multiply(vertical, v));
            direction = subtract(direction, camera_pos);

            Ray ray = {camera_pos, direction};
            
            double t;
            Color pixel_color = {255, 255, 255};
            if (intersect_ray_cylinder(ray, cylinder, &t))
            {
                pixel_color.r = 255;
                pixel_color.g = 0;
                pixel_color.b = 0;
            }

            image[j * width + i] = pixel_color;
        }
    }

    write_ppm("cylinder.ppm", image, width, height);

    free(image);
}

int main()
{
    ray_trace();
    return 0;
}
