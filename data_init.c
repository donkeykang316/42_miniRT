#include "minirt.h"

void    img_init(t_img  *image)
{
    image->aspect_ratio = 0;
    image->image_height = 0;
    image->image_width = 0;
}

void    camera_init(t_camera *camera)
{
    camera->focal_length = 0;
    camera->viewport_height = 0;
    camera->viewport_width = 0;
    camera->camera_center = vec_3d_init(0, 0, 0);
}