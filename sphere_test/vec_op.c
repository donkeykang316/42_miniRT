#include <stdio.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>

typedef struct  s_vector
{
    double  x;
    double  y;
    double  z;
}   t_vector;

t_vector vec_init(double x, double y, double z)
{
    t_vector vec;

    vec.x = x;
    vec.y = y;
    vec.z = z;
    return (vec);
}

t_vector    *vec_init_ptr(double x, double y, double z)
{
    t_vector *vec;

    vec = (t_vector *)malloc(sizeof(t_vector));
    vec->x = x;
    vec->y = y;
    vec->z = z;
    return (vec);
}

t_vector  multi_vec_vec(t_vector vec1, t_vector vec2)
{
    t_vector result;

    result = vec_init(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
    return (result);
}

int main()
{
    t_vector vec1;
    t_vector *vec2;
    t_vector result;

    vec1 = vec_init(1, 2, 3);
    vec2 = vec_init_ptr(4, 5, 6);
    result = multi_vec_vec(vec1, *vec2);
    printf("result: %f %f %f\n", result.x, result.y, result.z);
}