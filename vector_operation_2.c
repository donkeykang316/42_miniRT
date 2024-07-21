#include "minirt.h"

double  *add_vec_int(double *vec, int inte)
{
    int i;
    double *result;

    result = malloc(3 * sizeof(double));
    i = 0;
    while (i < 3)
    {
        result[i] = vec[i] + inte;
        i++;
    }
    
    return (result);
}

double  *subtrac_vec_int(double *vec, int inte)
{
    int i;
    double *result;

    result = malloc(3 * sizeof(double));
    i = 0;
    while (i < 3)
    {
        result[i] = vec[i] - inte;
        i++;
    }
    
    return (result);
}

double  *multi_vec_int(double *vec, int inte)
{
    int i;
    double *result;

    result = malloc(3 * sizeof(double));
    i = 0;
    while (i < 3)
    {
        result[i] = vec[i] * inte;
        i++;
    }
    
    return (result);
}

double  *divi_vec_int(double *vec, int inte)
{
    int i;
    double *result;

    result = malloc(3 * sizeof(double));
    i = 0;
    while (i < 3)
    {
        result[i] = vec[i] / inte;
        i++;
    }
    
    return (result);
}
