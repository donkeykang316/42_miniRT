#include "minirt.h"

void    secene_render(t_img *image, t_camera *camera, t_viewport *viewport)
{
    image_init(image);
    camera_init(camera, image);
    viewport_init(viewport, image, camera);
    render(image, camera, viewport);
}
