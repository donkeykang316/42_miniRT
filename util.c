#include "minirt.h"

unsigned int seed = 1;

unsigned int ft_rand(void) {
    // Implementing a simple LCG
    seed = (A * seed + C) % M;
    return seed;
}

double random_double(void) {
    // Normalize ft_rand() to produce a float in [0, 1)
    return ft_rand() / (M + 1.0);
}

double random_double_range(double min, double max) {
    // Map the random double to the range [min, max)
    return min + (max - min) * random_double();
}
