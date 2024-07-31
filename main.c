#include "minirt.h"

int main(void)
{
    t_camera    camera;

    camera_init(&camera);
    render(camera);
}