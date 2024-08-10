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

void    print_vector(t_vector v, int fd)
{
    ft_putstr_fd("x: ", fd);
    ft_putdouble_fd(v.x, fd);
    ft_putstr_fd("\ny: ", fd);
    ft_putdouble_fd(v.y, fd);
    ft_putstr_fd("\nz: ", fd);
    ft_putdouble_fd(v.z, fd);
    ft_putstr_fd("\n", fd);
}

void    print_camera(t_camera camera, int fd)
{
    ft_putstr_fd("camera:\n", fd);
    ft_putstr_fd("aspect_ratio: ", fd);
    ft_putdouble_fd(camera.aspect_ratio, fd);
    ft_putstr_fd("\nimage_width: ", fd);
    ft_putnbr_fd(camera.image_width, fd);
    ft_putstr_fd("\nsamples_per_pixel: ", fd);
    ft_putnbr_fd(camera.samples_per_pixel, fd);
    ft_putstr_fd("\nimage_height: ", fd);
    ft_putnbr_fd(camera.image_height, fd);
    ft_putstr_fd("\npixel_samples_scale: ", fd);
    ft_putdouble_fd(camera.pixel_samples_scale, fd);
    ft_putstr_fd("\nmax_depth: ", fd);
    ft_putnbr_fd(camera.max_depth, fd);
    ft_putstr_fd("\npixel_delta_u:\n", fd);
    print_vector(camera.pixel_delta_u, fd);
    ft_putstr_fd("pixel_delta_v:\n", fd);
    print_vector(camera.pixel_delta_v, fd);
    ft_putstr_fd("center:\n", fd);
    print_vector(camera.center, fd);
    ft_putstr_fd("pixel00_loc:\n", fd);
    print_vector(camera.pixel00_loc, fd);
    ft_putchar_fd('\n', fd);

}

void    print_sphere(t_sphere sphere, int fd)
{
    ft_putstr_fd("center:\n", fd);
    print_vector(sphere.center, fd);
    ft_putstr_fd("radius: ", fd);
    ft_putdouble_fd(sphere.radius, fd);
    ft_putchar_fd('\n', fd);
}

void    print_quad(t_quad quad, int fd)
{
    ft_putstr_fd("q:\n", fd);
    print_vector(quad.q, fd);
    ft_putstr_fd("u:\n", fd);
    print_vector(quad.u, fd);
    ft_putstr_fd("v:\n", fd);
    print_vector(quad.v, fd);
}

void    print_material(t_material material, int fd)
{
    ft_putstr_fd("albedo:\n", fd);
    print_vector(material.albedo, fd);
    ft_putstr_fd("fuzz: ", fd);
    ft_putdouble_fd(material.fuzz, fd);
    ft_putstr_fd("\ntype: ", fd);
    if (material.type == LAMBERTIAN)
        ft_putstr_fd("LAMBERTIAN\n", fd);
    else if (material.type == METAL)
        ft_putstr_fd("METAL\n", fd);
    else
        ft_putstr_fd("UNKNOWN\n", fd);
}

void    print_world(t_object **world, int fd)
{
    ft_putstr_fd("world:\n", fd);
    int i = 0;
    while (world[i])
    {
        if (world[i]->type == SPHERE)
        {
            ft_putstr_fd("sphere:\n", fd);
            print_sphere(world[i]->value.sphere, fd);
        }
        else if (world[i]->type == QUAD)
        {
            ft_putstr_fd("quad:\n", fd);
            print_quad(world[i]->value.quad, fd);
        }
        ft_putstr_fd("material:\n", fd);
        print_material(world[i]->material, fd);
        i++;
    }
}

void    print_ray(t_ray ray, int fd)
{
    ft_putstr_fd("ray:\n", fd);
    ft_putstr_fd("origin:\n", fd);
    print_vector(ray.origin, fd);
    ft_putstr_fd("direction:\n", fd);
    print_vector(ray.direction, fd);
}

void    print_rec(t_hit_rec rec, int fd)
{
    ft_putstr_fd("rec:\n", fd);
    ft_putstr_fd("p:\n", fd);
    print_vector(rec.hit_point, fd);
    ft_putstr_fd("normal:\n", fd);
    print_vector(rec.normal, fd);
    ft_putstr_fd("material:\n", fd);
    print_material(rec.material, fd);
    ft_putstr_fd("t: ", fd);
    ft_putdouble_fd(rec.hit_distance, fd);
    ft_putstr_fd("\nfront_face: ", fd);
    ft_putnbr_fd(rec.front_face, fd);
    ft_putstr_fd("\nobject_index: ", fd);
    ft_putnbr_fd(rec.object_index, fd);
    ft_putchar_fd('\n', fd);
}
