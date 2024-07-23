#include "minirt.h"

void    *safe_malloc(size_t size, char *error)
{
    malloc(size);
    perror(error);
}