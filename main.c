#include "minirt.h"

void    image_init(t_img  *image)
{
    image->aspect_ratio = 16.0 / 9.0;
    image->image_width = 400;
    image->image_height = (int)(image->image_width / image->aspect_ratio);
    if (image->image_height < 1)
        image->image_height = 1;
}

void    camera_init(t_camera *camera, t_img *image)
{
    camera->focal_length = 1.0;
    camera->viewport_height = 2.0;
    camera->viewport_width = camera->viewport_height * (double)(image->image_width / image->image_height);
    camera->camera_center = vec_init(0, 0, 0);
}

void   viewport_init(t_viewport *viewport, t_img *image, t_camera *camera)
{
    t_vector    *vec;

    vec = vec_init(0, 0, camera->focal_length);
    viewport->viewport_u = vec_init(camera->viewport_width, 0, 0);
    viewport->viewport_v = vec_init(0, -(camera->viewport_height), 0);
    viewport->pixel_delta_u = divi_vec_int(viewport->viewport_u, image->image_width);
    viewport->pixel_delta_v = divi_vec_int(viewport->viewport_v, image->image_height);
    viewport->viewport_upper_left = subtrac_vec_vec(camera->camera_center, add_vec_vec(vec, add_vec_vec(divi_vec_int(viewport->viewport_u, 2), divi_vec_int(viewport->viewport_v, 2))));
    viewport->pixel00_loc = add_vec_vec(viewport->viewport_upper_left, multi_vec_doub(add_vec_vec(viewport->pixel_delta_u, viewport->pixel_delta_v), 0.5));
    free(vec);
} 

t_vector    *ray_color(t_ray *ray)
{
    t_vector    *ray_color;
    t_vector    *unit_direction;
    double       a;
    t_vector    *color1;
    t_vector    *color2;
    
    ray_color = malloc(sizeof(t_vector));
    color1 = vec_init(1.0, 1.0, 1.0);
    color2 = vec_init(0.5, 0.7, 1.0);
    unit_direction = vec_init(ray->direction->x, ray->direction->y, ray->direction->z);
    a = 0.5 * (unit_direction->y + 1.0);
    ray_color = add_vec_vec(multi_vec_doub(color1, (1.0 - a)), multi_vec_doub(color2, a));
    free(color1);
    free(color2);
    free(unit_direction);
    return (ray_color);
}

void    write_color(t_vector *pixel_color)
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

void    render(t_img *image, t_camera *camera, t_viewport *viewport)
{
    t_vector    *pixel_center;
    t_vector    *pixel_color;
    t_ray       *ray;
    int         i;
    int         j;

    i = 0;
    j = 0;
    ray = malloc(sizeof(t_ray));
    printf("P3\n%d %d\n255\n", (int)image->image_width, (int)image->image_height);
    while (j < image->image_height)
    {
        i = 0;
        while (i < image->image_width)
        {
            pixel_center = add_vec_vec(viewport->pixel00_loc, add_vec_vec(multi_vec_int(viewport->pixel_delta_u, i), multi_vec_int(viewport->pixel_delta_v, j)));
            ray->direction = subtrac_vec_vec(pixel_center, camera->camera_center);
            ray->origin = vec_init(camera->camera_center->x, camera->camera_center->y, camera->camera_center->z);
            pixel_color = ray_color(ray);
            write_color(pixel_color);
            free(pixel_center);
            free(pixel_color);
            free(ray->origin);
            free(ray->direction);
            i++;
        }
        j++;
    }
    

}

void    secene_render(t_img *image, t_camera *camera, t_viewport *viewport)
{
    image_init(image);
    camera_init(camera, image);
    viewport_init(viewport, image, camera);
    render(image, camera, viewport);
}

int main(void)
{
    t_img       image;
    t_camera    camera;
    t_viewport  viewport;

    secene_render(&image, &camera, &viewport);
}