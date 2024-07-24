#include "minirt.h"

void    secene_render(t_camera *camera)
{
    camera_init(camera);
    render(camera);
}
