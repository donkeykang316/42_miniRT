#include "minirt.h"

double  *add_vec_doub(double *vec, double doub)
{
    int i;
    double *result;

    result = malloc(3 * sizeof(double));
    i = 0;
    while (i < 3)
    {
        result[i] = vec[i] + doub;
        i++;
    }
    
    return (result);
}

double  *subtrac_vec_doub(double *vec, double doub)
{
    int i;
    double *result;

    result = malloc(3 * sizeof(double));
    i = 0;
    while (i < 3)
    {
        result[i] = vec[i] - doub;
        i++;
    }
    
    return (result);
}

double  *multi_vec_doub(double *vec, double doub)
{
    int i;
    double *result;

    result = malloc(3 * sizeof(double));
    i = 0;
    while (i < 3)
    {
        result[i] = vec[i] * doub;
        i++;
    }
    
    return (result);
}

double  *divi_vec_doub(double *vec, double doub)
{
    int i;
    double *result;

    result = malloc(3 * sizeof(double));
    i = 0;
    while (i < 3)
    {
        result[i] = vec[i] / doub;
        i++;
    }
    
    return (result);
}
