#include "minirt.h"

int main(void)
{
    t_img       image;
    t_camera    camera;
    t_viewport  viewport;

    secene_render(&image, &camera, &viewport);
}