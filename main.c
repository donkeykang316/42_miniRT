#include "minirt.h"

void    add_camera(t_img *image, t_camera *camera)
{
    double  *viewport_u;
    double  *viewport_v;
    double  *pixel_delta_u;
    double  *pixel_delta_v;
    double  *temp;
    double  *viewport_upper_left;
    double  *pixel00_loc;

    image->aspect_ratio = 16.0 / 9.0;
    image->image_width = 400;
    image->image_height = (int)(image->image_width / image->aspect_ratio);
    if (image->image_height < 1)
        image->image_height = 1;
    camera->focal_length = 1.0;
    camera->viewport_height = 1.0;
    camera->viewport_width = camera->viewport_height * (double)(image->image_width / image->image_height);
    viewport_u = vec_3d_init(camera->viewport_width, 0, 0);
    viewport_v = vec_3d_init(0, -(camera->viewport_height), 0);
    pixel_delta_u = divi_vec_int(viewport_u, image->image_width);
    pixel_delta_v = divi_vec_int(viewport_v, image->image_height);
    temp = vec_3d_init(0, 0, camera->focal_length);
    viewport_upper_left = subtrac_vec_vec(subtrac_vec_vec(subtrac_vec_vec(camera->camera_center, temp), divi_vec_int(viewport_u, 2)), divi_vec_int(viewport_v, 2));
    pixel00_loc = add_vec_vec(viewport_upper_left, multi_vec_doub(add_vec_vec(pixel_delta_u, pixel_delta_v), 0.5));
    render(image, camera, pixel00_loc, pixel_delta_u, pixel_delta_v);
}

int main(void)
{
    t_img       image;
    t_camera    camera;

    img_init(&image);
    camera_init(&camera);
    add_camera(&image, &camera);
}