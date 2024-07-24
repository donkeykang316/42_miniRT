#include "minirt.h"

double  degrees_to_radians(double degrees)
{
    double  radian;

    radian = degrees * PI /180.0;
    return (radian);
}

int ft_rand()
{
    static unsigned int rand_seed = 1;

    rand_seed = (RAND_A * rand_seed + RAND_C) % RAND_M;
    return ((int)(rand_seed & 0x7FFFFFFF));
}

double  random_double_a()
{
    double  rd;
    rd = rand() / (RAND_MAX + 1.0);
    return (rd);
}

double  random_double(double min, double max)
{
    double  rd;
    rd =  min + (max-min) * random_double_a();
    return (rd);
}
