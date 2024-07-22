#include "minirt.h"

//type 1
void simple_render()
{
    int img_width;
    int img_height;
    int i;
    int j;
    double  r;
    double  g;
    double  b;
    int     ir;
    int     ig;
    int     ib;

    img_width = 700;
    img_height = 700;
    i = 0;
    j = 0;
    r = 0.0;
    g = 0.0;
    b = 0.0;
    ir = 0;
    ig = 0;
    ib = 0;

    printf("P3\n%d %d\n255\n", img_width, img_height);
    while (j < img_height)
    {
        i = 0;
        while (i < img_width)
        {
            r = (double)i / (img_width - 1);
            g = (double)j / (img_height - 1);
            ir = (int)255.999 * r;
            ig = (int)255.999 * g;
            ib = (int)255.999 * b;
            printf("%d %d %d\n", ir, ig, ib);
            i++;
        }
        j++;
    }
}

//type 2
void    alt_write_color(double *e)
{
    double  r;
    double  g;
    double  b;
    int     rbyte;
    int     gbyte;
    int     bbyte;

    r = e[0];
    g = e[1];
    b = e[2];
    rbyte = (int)255.999 * r;
    gbyte = (int)255.999 * g;
    bbyte = (int)255.999 * b;
    printf("%d %d %d\n", rbyte, gbyte, bbyte);
}

void    alt_render()
{
    int     img_width;
    int     img_height;
    int     i;
    int     j;
    double  e[3];

    img_width = 700;
    img_height = 700;
    i = 0;
    j = 0;
    e[0] = 0;
    e[1] = 0;
    e[2] = 0;

    printf("P3\n%d %d\n255\n", img_width, img_height);
    while (j < img_height)
    {
        i = 0;
        while (i < img_width)
        {
            e[0] = (double)i / (img_width - 1);
            e[1] = (double)j / (img_height - 1);
            alt_write_color(e);
            i++;
        }
        j++;
    }
}
