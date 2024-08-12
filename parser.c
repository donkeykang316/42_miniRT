#include "minirt.h"

int parse_space(char** scene, int* total) {
    int parsed = 0;
    while(isspace((*scene)[parsed])) {
        parsed++;
    }
    *scene += parsed;
    *total += parsed;
    return parsed;
}

int parse_char(char** scene, char c, int* total) {
    int parsed = 0;
    if (**scene == c)
        parsed = 1;
    *scene += parsed;
    *total += parsed;
    return parsed;
}

int parse_whitespace(char** scene, int* total) {
    int parsed = 0;
    while((*scene)[parsed] == ' ') {
        parsed++;
    }
    *scene += parsed;
    *total += parsed;
    return parsed;
}

int parse_decimal(char** scene, int* dst, int* total) {
    int parsed = 0;
    *dst = 0;

    while(isdigit((*scene)[parsed])) {
        *dst = *dst * 10 + ((*scene)[parsed] - '0');
        parsed++;
    }

    *scene += parsed;
    *total += parsed;
    return parsed;
}

double make_double(int whole, int fraction) {
    double f = fraction;
    while(f > 1.)
        f /= 10.;
    return (double)(whole) + f;
}

int parse_double(char** scene, double* flt, int* total) {
    int parsed = 0;
    int whole = 0;
    int fraction = 0;
    char* sc = *scene;

    int minus = parse_char(&sc, '-', &parsed);
    parse_decimal(&sc, &whole, &parsed);
    if (parse_char(&sc, '.', &parsed))
        parse_decimal(&sc, &fraction, &parsed);
    if (!(parsed - minus) || ((parsed - minus) == 1 && (*scene)[minus] == '.'))
        return 0;
    *flt = make_double(whole, fraction);
    if (minus)
        *flt = -*flt;
    *scene += parsed;
    *total += parsed;
    return parsed;
}

int parse_byte(char** scene, int* byte, int* total) {
    int parsed = 0;
    char* sc = *scene;
    if (!parse_decimal(&sc, byte, &parsed))
        return 0;
    if ((parsed > 3) || (*byte > 255))
        return 0;
    *total += parsed;
    *scene += parsed;
    return parsed;
}

int parse_color(char** scene, t_vector* clr, int* total) {
    int parsed = 0;
    char* sc = *scene;
    int rgb[3];

    if (!parse_byte(&sc, &rgb[0], &parsed))
        return 0;
    if (!parse_char(&sc, ',', &parsed))
        return 0;
    if (!parse_byte(&sc, &rgb[1], &parsed))
        return 0;
    if (!parse_char(&sc, ',', &parsed))
        return 0;
    if (!parse_byte(&sc, &rgb[2], &parsed))
        return 0;
    clr->x = rgb[0] / 255.;
    clr->y = rgb[1] / 255.;
    clr->z = rgb[2] / 255.;

    *scene += parsed;
    *total += parsed;
    return parsed;
}

int parse_vector(char** scene, t_vector* vec, int* total) {
    int parsed = 0;
    char* sc = *scene;

    if (!parse_double(&sc, &vec->x, &parsed))
        return 0;
    if (!parse_char(&sc, ',', &parsed))
        return 0;
    if (!parse_double(&sc, &vec->y, &parsed))
        return 0;
    if (!parse_char(&sc, ',', &parsed))
        return 0;
    if (!parse_double(&sc, &vec->z, &parsed))
        return 0;
    *total += parsed;
    *scene += parsed;
    return parsed;
}

int parse_ambient_light(char** _scene, t_amblight* light, int* total) {
    char* scene = *_scene;
    int parsed = 0;

    if (!parse_char(&scene, 'A', &parsed))
        return 0;
    if (!parse_space(&scene, &parsed))
        return 0;
    if (!parse_double(&scene, &light->intensity, &parsed))
        return 0;
    if (!parse_space(&scene, &parsed))
        return 0;
    if (!parse_color(&scene, &light->color, &parsed))
        return 0;

    *_scene += parsed;
    *total += parsed;
    return parsed;
}

int parse_camera(char** _scene, t_camera* camera, int* total) {
    char* scene = *_scene;
    int parsed = 0;
    t_vector orientation;

    if (!parse_char(&scene, 'C', &parsed))
        return 0;
    if (!parse_space(&scene, &parsed))
        return 0;
    if (!parse_vector(&scene, &camera->center, &parsed))
        return 0;
    if (!parse_space(&scene, &parsed))
        return 0;
    if (!parse_vector(&scene, &orientation, &parsed))
        return 0;
    if (!parse_space(&scene, &parsed))
        return 0;
    if (!parse_double(&scene, &camera->hfov, &parsed))
        return 0;
    camera->aspect_ratio = 16./9.;
    if (vec_length(orientation) != 1.)
        return 0;
    camera->lookat = orientation;
    *total += parsed;
    *_scene += parsed;
    return parsed;
}

void add_light(t_world* world, t_light light) {
    t_light* lights = ft_calloc(world->point_lights_len + 1, sizeof(t_light));
    ft_memcpy(lights, world->point_lights, world->point_lights_len * sizeof(t_light));
    lights[world->point_lights_len] = light;
    if (world->point_lights)
        free(world->point_lights);
    world->point_lights = lights;
    world->point_lights_len++;
}

void add_object(t_world* world, t_object object) {
    t_object* objects = ft_calloc(world->objects_len + 1, sizeof(t_object));
    ft_memcpy(objects, world->objects, world->objects_len * sizeof(t_object));
    objects[world->objects_len] = object;
    if (world->objects)
        free(world->objects);
    world->objects = objects;
    world->objects_len++;
}

int parse_light(char** _scene, t_world* world, int* total) {
    char* scene = *_scene;
    int parsed = 0;
    t_light light;

    if (!parse_char(&scene, 'L', &parsed))
        return 0;
    if (!parse_space(&scene, &parsed))
        return 0;
    if (!parse_vector(&scene, &light.position, &parsed))
        return 0;
    if (!parse_space(&scene, &parsed))
        return 0;
    if (!parse_double(&scene, &light.intensity, &parsed))
        return 0;
    if (!parse_space(&scene, &parsed))
        return 0;
    if (!parse_color(&scene, &light.color, &parsed))
        return 0;
    if (light.intensity < 0 || light.intensity > 1)
        return 0;
    add_light(world, light);
    *total += parsed;
    *_scene += parsed;
    return parsed;
}

int parse_string(char** scene, char* str, int* total) {
    int parsed = 0;
    while(str[parsed] && (*scene)[parsed] && str[parsed] == (*scene)[parsed]) {
        parsed++;
    }
    if (str[parsed])
        return 0;
    *scene += parsed;
    *total += parsed;
    return parsed;
}

int parse_sphere(char** _scene, t_world* world, int* total) {
    char* scene = *_scene;
    int parsed = 0;
    double diameter;
    t_object obj;
    obj.type = SPHERE;
    obj.material.fuzz = 0.1;
    obj.material.ref_idx = 0.5;
    obj.material.type = LAMBERTIAN;

    if (!parse_string(&scene, "sp", &parsed))
        return 0;
    if (!parse_space(&scene, &parsed))
        return 0;
    if (!parse_vector(&scene, &obj.value.sphere.center, &parsed))
        return 0;
    if (!parse_space(&scene, &parsed))
        return 0;
    if (!parse_double(&scene, &diameter, &parsed))
        return 0;
    if (!parse_space(&scene, &parsed))
        return 0;
    if (!parse_color(&scene, &obj.material.albedo, &parsed))
        return 0;
    if (diameter < 0)
        return 0;
    obj.value.sphere.radius = diameter / 2;
    add_object(world, obj);
    *total += parsed;
    *_scene += parsed;
    return parsed;
}

int parse_cylinder(char** _scene, t_world* world, int* total) {
    char* scene = *_scene;
    int parsed = 0;
    double diameter;
    t_object obj;
    obj.type = CYLINDER;
    obj.material.fuzz = 0.1;
    obj.material.ref_idx = 0.5;
    obj.material.type = LAMBERTIAN;

    if (!parse_string(&scene, "cy", &parsed))
        return 0;
    if (!parse_space(&scene, &parsed))
        return 0;
    if (!parse_vector(&scene, &obj.value.cyllinder.center, &parsed))
        return 0;
    if (!parse_space(&scene, &parsed))
        return 0;
    if (!parse_vector(&scene, &obj.value.cyllinder.axis, &parsed))
        return 0;
    if (!parse_space(&scene, &parsed))
        return 0;
    if (!parse_double(&scene, &diameter, &parsed))
        return 0;
    if (!parse_space(&scene, &parsed))
        return 0;
    if (!parse_double(&scene, &obj.value.cyllinder.height, &parsed))
        return 0;
    if (!parse_space(&scene, &parsed))
        return 0;
    if (!parse_color(&scene, &obj.material.albedo, &parsed))
        return 0;
    if (diameter < 0 || obj.value.cyllinder.height < 0 || vec_length(obj.value.cyllinder.axis) != 1.)
        return 0;
    obj.value.cyllinder.radius = diameter / 2;
    add_object(world, obj);
    *total += parsed;
    *_scene += parsed;
    return parsed;
}


int parse_triangle(char** _scene, t_world* world, int* total) {
    char* scene = *_scene;
    int parsed = 0;
    t_object obj;
    obj.type = TRIANGLE;
    obj.material.fuzz = 0.1;
    obj.material.ref_idx = 0.5;
    obj.material.type = LAMBERTIAN;

    if (!parse_string(&scene, "tr", &parsed))
        return 0;
    if (!parse_space(&scene, &parsed))
        return 0;
    if (!parse_vector(&scene, &obj.value.triangle.q, &parsed))
        return 0;
    if (!parse_space(&scene, &parsed))
        return 0;
    if (!parse_vector(&scene, &obj.value.triangle.u, &parsed))
        return 0;
    if (!parse_space(&scene, &parsed))
        return 0;
    if (!parse_color(&scene, &obj.material.albedo, &parsed))
        return 0;
    add_object(world, obj);
    *total += parsed;
    *_scene += parsed;
    return parsed;
}

int parse_world(char* scene, t_world* world) {
    int parsed = 0;
    ft_memset(world, 0, sizeof(t_world));

    while(1) {
        parse_space(&scene, &parsed);
        if (parse_ambient_light(&scene, &world->ambient_light, &parsed))
            continue;
        if (parse_camera(&scene, &world->camera, &parsed))
            continue;
        if (parse_light(&scene, world, &parsed))
            continue;
        if (parse_sphere(&scene, world, &parsed))
            continue;
        if (parse_cylinder(&scene, world, &parsed))
            continue;
        if (parse_triangle(&scene, world, &parsed))
            continue;
        if (*scene == 0)
            break;
        // printf("error at %s\n", scene);
        return 0;
    }
    
    return parsed;
}