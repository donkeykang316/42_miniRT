#include "minirt.h"

void    write_color(double *color_final)
{
    double  r;
    double  g;
    double  b;
    int     rbyte;
    int     gbyte;
    int     bbyte;

    r = color_final[0];
    g = color_final[1];
    b = color_final[2];
    rbyte = (int)255.999 * r;
    gbyte = (int)255.999 * g;
    bbyte = (int)255.999 * b;
    printf("%d %d %d\n", rbyte, gbyte, bbyte);
}

void  ray_color_print(double *ray_direction)
{
    double  *a;
    double  *tmp;
    double  *color1;
    double  *color2;
    double  *color3;
    double  *color_final;
    
    ray_direction[1] += 1.0;
    a = multi_vec_doub(ray_direction, 0.5);
    tmp = multi_vec_int(a, -1);
    color1 = vec_3d_init(1.0, 1.0, 1.0);
    color2 = vec_3d_init(0.5, 0.7, 1.0);
    color3 = multi_vec_vec(add_vec_doub(tmp, 1.0), color1);
    color_final = add_vec_vec(multi_vec_vec(a, color2), color3);
    write_color(color_final);
}

void    render(t_img *image, t_camera *camera, double *pixel00_loc, double *pixel_delta_u, double *pixel_delta_v)
{
    int     i;
    int     j;
    double  *pixel_center;
    double  *ray_direction;

    image->image_width = 700;
    image->image_height = 700;
    i = 0;
    j = 0;

    printf("P3\n%d %d\n255\n", image->image_width, image->image_height);
    while (j < image->image_height)
    {
        i = 0;
        while (i < image->image_width)
        {
            pixel_center = add_vec_vec(pixel00_loc, add_vec_vec(multi_vec_int(pixel_delta_u, i), multi_vec_int(pixel_delta_v, j)));
            ray_direction = subtrac_vec_vec(pixel_center, camera->camera_center);
            printf("%d %d %d\n", (int)camera->camera_center[0], (int)camera->camera_center[1], (int)camera->camera_center[2]);
            printf("%d %d %d\n", (int)ray_direction[0], (int)ray_direction[1], (int)ray_direction[2]);
            ray_color_print(ray_direction);
            i++;
        }
        j++;
    }
}
