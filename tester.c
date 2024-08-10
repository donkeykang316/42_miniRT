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
    ft_putstr_fd("lookfrom:\n", fd);
    print_vector(camera.lookfrom, fd);
    ft_putstr_fd("lookat:\n", fd);
    print_vector(camera.lookat, fd);
    ft_putstr_fd("vfov: ", fd);
    ft_putdouble_fd(camera.vfov, fd);
    ft_putstr_fd("\n", fd);
}

void    print_sphere(t_sphere sphere, int fd)
{
    ft_putstr_fd("center:\n", fd);
    print_vector(sphere.center, fd);
    ft_putstr_fd("radius: ", fd);
    ft_putdouble_fd(sphere.radius, fd);
    ft_putstr_fd("\nmaterial:\n", fd);
    print_material(*sphere.material, fd);
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
    ft_putstr_fd("material:\n", fd);
    print_material(*quad.material, fd);
}

void    print_tri(t_tri tri, int fd)
{
    ft_putstr_fd("tri:\n", fd);
    ft_putstr_fd("q:\n", fd);
    print_vector(tri.q, fd);
    ft_putstr_fd("u:\n", fd);
    print_vector(tri.u, fd);
    ft_putstr_fd("v:\n", fd);
    print_vector(tri.v, fd);
    ft_putstr_fd("material:\n", fd);
    print_material(*tri.material, fd);
}

void    print_cylinder(t_cylinder cyl, int fd)
{
    ft_putstr_fd("center:\n", fd);
    print_vector(cyl.center, fd);
    ft_putstr_fd("axis:\n", fd);
    print_vector(cyl.axis, fd);
    ft_putstr_fd("radius: ", fd);
    ft_putdouble_fd(cyl.radius, fd);
    ft_putstr_fd("\nheight: ", fd);
    ft_putdouble_fd(cyl.height, fd);
    ft_putstr_fd("\nmaterial:\n", fd);
    print_material(*cyl.material, fd);
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

void    print_world(t_object_list **world, int fd)
{
    int i;

    i = 0;
    while (world[i])
    {
        if (world[i]->type == SPHERE)
            print_sphere(*world[i]->sphere, fd);
        else if (world[i]->type == QUAD)
            print_quad(*world[i]->quad, fd);
        else if (world[i]->type == TRIANGLE)
            print_tri(*world[i]->tri, fd);
        else if (world[i]->type == CYLINDER)
            print_cylinder(*world[i]->cyl, fd);
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
    print_vector(rec.p, fd);
    ft_putstr_fd("normal:\n", fd);
    print_vector(rec.normal, fd);
    ft_putstr_fd("material:\n", fd);
    print_material(*rec.material, fd);
    ft_putstr_fd("t: ", fd);
    ft_putdouble_fd(rec.t, fd);
    ft_putstr_fd("\nfront_face: ", fd);
    ft_putnbr_fd(rec.front_face, fd);
    ft_putstr_fd("\nobject_index: ", fd);
    ft_putnbr_fd(rec.object_index, fd);
    ft_putchar_fd('\n', fd);
}

void    print_light(t_light light, int fd)
{
    ft_putstr_fd("light:\n", fd);
    ft_putstr_fd("position:\n", fd);
    print_vector(light.position, fd);
    ft_putstr_fd("intensity:\n", fd);
    ft_putdouble_fd(light.intensity, fd);
}

void    print_amblight(t_amblight amblight, int fd)
{
    ft_putstr_fd("amblight:\n", fd);
    ft_putstr_fd("intensity:\n", fd);
    ft_putdouble_fd(amblight.intensity, fd);
}

void    print_parser(t_parser *parser, int fd)
{
    ft_putstr_fd("parser:\n", fd);
    ft_putstr_fd("count: ", fd);
    ft_putnbr_fd(parser->count, fd);
    ft_putstr_fd("\n", fd);
    print_amblight(*parser->amblight, fd);
    print_camera(*parser->camera, fd);
    print_light(*parser->light, fd);
    print_world(parser->object_list, fd);
}