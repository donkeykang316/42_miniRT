#include "minirt.h"

t_vector  add_vec_doub(t_vector vec, double doub)
{
    t_vector result;

    result.x = vec.x + doub;
    result.y = vec.y + doub;
    result.z = vec.z + doub;
    return (result);
}

t_vector  subtrac_vec_doub(t_vector vec, double doub)
{
    t_vector result;

    result.x = vec.x - doub;
    result.y = vec.y - doub;
    result.z = vec.z - doub;
    return (result);
}

t_vector  multi_vec_doub(t_vector vec, double doub)
{
    t_vector result;

    result.x = vec.x * doub;
    result.y = vec.y * doub;
    result.z = vec.z * doub;
    return (result);
}

t_vector  divi_vec_doub(t_vector vec, double doub)
{
    t_vector result;

    result.x = vec.x / doub;
    result.y = vec.y / doub;
    result.z = vec.z / doub;
    return (result);
}
