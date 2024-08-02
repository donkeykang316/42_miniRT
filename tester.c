#include "minirt.h"

void    ft_putdouble_fd(double n, int fd)
{
    char    c;
    int     precision = 6;

    // Handle negative numbers
    if (n < 0)
    {
        write(fd, "-", 1);
        n = -n;
    }

    // Extract and print integer part
    long long int_part = (long long)n;
    double fraction_part = n - int_part;

    if (int_part == 0)
        write(fd, "0", 1);
    else
    {
        // Recursive function to print each digit of integer part
        if (int_part >= 10)
            ft_putdouble_fd(int_part / 10, fd); // Use precision 0 here for recursive calls
        c = (int_part % 10) + '0';
        write(fd, &c, 1);
    }

    // If precision is zero, no need to print decimal point
    if (precision == 0)
        return;

    // Print decimal point
    write(fd, ".", 1);

    // Print fractional part up to specified precision
    while (precision-- > 0)
    {
        fraction_part *= 10;
        int digit = (int)fraction_part;
        c = digit + '0';
        write(fd, &c, 1);
        fraction_part -= digit;
    }
}

void    print_vector(t_vector v)
{
    ft_putstr_fd("x: ", 2);
    ft_putdouble_fd(v.x, 2);
    ft_putstr_fd("\ny: ", 2);
    ft_putdouble_fd(v.y, 2);
    ft_putstr_fd("\nz: ", 2);
    ft_putdouble_fd(v.z, 2);
    ft_putstr_fd("\n", 2);
}

void    print_camera(t_camera camera)
{
    ft_putstr_fd("camera:\n", 2);
    ft_putstr_fd("aspect_ratio: ", 2);
    ft_putdouble_fd(camera.aspect_ratio, 2);
    ft_putstr_fd("\nimage_width: ", 2);
    ft_putnbr_fd(camera.image_width, 2);
    ft_putstr_fd("\nsamples_per_pixel: ", 2);
    ft_putnbr_fd(camera.samples_per_pixel, 2);
    ft_putstr_fd("\nimage_height: ", 2);
    ft_putnbr_fd(camera.image_height, 2);
    ft_putstr_fd("\npixel_samples_scale: ", 2);
    ft_putdouble_fd(camera.pixel_samples_scale, 2);
    ft_putstr_fd("\nmax_depth: ", 2);
    ft_putnbr_fd(camera.max_depth, 2);
    ft_putstr_fd("\npixel_delta_u:\n", 2);
    print_vector(camera.pixel_delta_u);
    ft_putstr_fd("pixel_delta_v:\n", 2);
    print_vector(camera.pixel_delta_v);
    ft_putstr_fd("center:\n", 2);
    print_vector(camera.center);
    ft_putstr_fd("pixel00_loc:\n", 2);
    print_vector(camera.pixel00_loc);
    ft_putchar_fd('\n', 2);

}

void    print_sphere(t_sphere sphere)
{
    ft_putstr_fd("center:\n", 2);
    print_vector(sphere.center);
    ft_putstr_fd("radius: ", 2);
    ft_putdouble_fd(sphere.radius, 2);
    ft_putstr_fd("\nmaterial:\n", 2);
    print_material(*sphere.material);
    ft_putchar_fd('\n', 2);
}

void    print_quad(t_quad quad)
{
    ft_putstr_fd("q:\n", 2);
    print_vector(quad.q);
    ft_putstr_fd("u:\n", 2);
    print_vector(quad.u);
    ft_putstr_fd("v:\n", 2);
    print_vector(quad.v);
    ft_putstr_fd("material:\n", 2);
    print_material(*quad.material);
}

void    print_material(t_material material)
{
    ft_putstr_fd("albedo:\n", 2);
    print_vector(material.albedo);
    ft_putstr_fd("fuzz: ", 2);
    ft_putdouble_fd(material.fuzz, 2);
    ft_putstr_fd("\ntype: ", 2);
    if (material.type == LAMBERTIAN)
        ft_putstr_fd("LAMBERTIAN\n", 2);
    else if (material.type == METAL)
        ft_putstr_fd("METAL\n", 2);
    else
        ft_putstr_fd("UNKNOWN\n", 2);
}

void    print_world(t_object_list **world)
{
    ft_putstr_fd("world:\n", 2);
    int i = 0;
    while (world[i])
    {
        if (world[i]->type == SPHERE)
        {
            ft_putstr_fd("sphere:\n", 2);
            print_sphere(*world[i]->sphere);
        }
        else if (world[i]->type == QUAD)
        {
            ft_putstr_fd("quad:\n", 2);
            print_quad(*world[i]->quad);
        }
        i++;
    }
}

void    print_ray(t_ray ray)
{
    ft_putstr_fd("ray:\n", 2);
    ft_putstr_fd("origin:\n", 2);
    print_vector(ray.origin);
    ft_putstr_fd("direction:\n", 2);
    print_vector(ray.direction);
}

void    print_rec(t_hit_rec rec)
{
    ft_putstr_fd("rec:\n", 2);
    ft_putstr_fd("p:\n", 2);
    print_vector(rec.p);
    ft_putstr_fd("normal:\n", 2);
    print_vector(rec.normal);
    ft_putstr_fd("material:\n", 2);
    print_material(*rec.material);
    ft_putstr_fd("t: ", 2);
    ft_putdouble_fd(rec.t, 2);
    ft_putstr_fd("\nfront_face: ", 2);
    ft_putnbr_fd(rec.front_face, 2);
    ft_putstr_fd("\nobject_index: ", 2);
    ft_putnbr_fd(rec.object_index, 2);
    ft_putchar_fd('\n', 2);
}