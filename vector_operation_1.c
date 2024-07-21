#include "minirt.h"

double  *add_vec_vec(double *vec1, double *vec2)
{
    int i;
    double *result;

    result = malloc(3 * sizeof(double));
    i = 0;
    while (i < 3)
    {
        result[i] = vec1[i] + vec2[i];
        i++;
    }
    
    return (result);
}

double  *subtrac_vec_vec(double *vec1, double *vec2)
{
    int i;
    double *result;

    result = malloc(3 * sizeof(double));
    i = 0;
    while (i < 3)
    {
        result[i] = vec1[i] - vec2[i];
        i++;
    }
    
    return (result);
}

double  *multi_vec_vec(double *vec1, double *vec2)
{
    int i;
    double *result;

    result = malloc(3 * sizeof(double));
    i = 0;
    while (i < 3)
    {
        result[i] = vec1[i] * vec2[i];
        i++;
    }
    
    return (result);
}

double  *divi_vec_vec(double *vec1, double *vec2)
{
    int i;
    double *result;

    result = malloc(3 * sizeof(double));
    i = 0;
    while (i < 3)
    {
        result[i] = vec1[i] / vec2[i];
        i++;
    }
    
    return (result);
}

