#include "minirt.h"

t_vector    unit_vector(t_vector vec)
{
    t_vector    result;

    result = divi_vec_doub(vec, vec_length(vec));
    return (result);
}

t_vector    normalize_vec(t_vector vec)
{
    double length;
    t_vector result;
    
    length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    result = vec_init(vec.x / length, vec.y / length, vec.z / length);
    return (result);
}
