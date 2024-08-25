#include "minirt.h"

void print_material(t_material material) {
    t_vec c = material.albedo;
    printf("\t\t\t[material]\n\t\t\t\talbedo=(%.2f,%.2f,%.2f)\n", c.x, c.y, c.z);
}

void print_sphere(t_object sphere) {
    t_vec center = sphere.value.sphere.center;
    printf("\t\t[sphere]\n\t\t\tcenter=(%.2f, %.2f, %.2f)\n\t\t\tradius=%f\n", center.x, center.y, center.z, sphere.value.sphere.radius);
}

void print_cylinder(t_object cylinder) {
    t_vec center = cylinder.value.cylinder.center;
    t_vec axis = cylinder.value.cylinder.axis;
    printf("\t\t[cylinder]\n\t\t\tcenter=(%.2f, %.2f, %.2f)\n\t\t\taxis=(%.2f, %.2f, %.2f)\n",
        center.x, center.y, center.z, axis.x, axis.y, axis.z);
}
void print_plane(t_object plane) {
    t_vec point = plane.value.plane.point;
    t_vec normal = plane.value.plane.normal;
    printf("\t\t[plane]\n\t\t\tpoint=(%.2f, %.2f, %.2f)\n\t\t\tnormal=(%.2f, %.2f, %.2f)\n",
        point.x, point.y, point.z, normal.x, normal.y, normal.z);
}

void print_ambient_light(t_amblight light) {
    printf("\t[ambient light]\n\t\tcolor=(%.2f, %.2f, %.2f)\n\t\tintensity=%f\n", light.color.x, light.color.y, light.color.z, light.intensity);
}

void print_point_lights(t_world* world) {
    printf("\t[point lights]\n");
    for(int i = 0; i < world->point_lights_len; i++) {
        t_light light = world->point_lights[i];
        printf("\t\t[point light]\n\t\t\tcolor=(%.2f, %.2f, %.2f)\n\t\t\tposition=(%.2f, %.2f, %.2f)\n\t\t\tintensity=%.2f\n", light.color.x, light.color.y, light.color.z, light.position.x, light.position.y, light.position.z, light.intensity);
    }
}

void print_world(t_world* world) {
    printf("[world]\n\t[objects]\n");
    for(int i = 0; i < world->objects_len; i++) {
        if (world->objects[i].type == OBJECT_TYPE_SPHERE)
            print_sphere(world->objects[i]);
        else if (world->objects[i].type == OBJECT_TYPE_CYLINDER)
            print_cylinder(world->objects[i]);
        else if (world->objects[i].type == OBJECT_TYPE_PLANE)
            print_plane(world->objects[i]);
        else
            printf("\t\t[unknown]\n");
        print_material(world->objects[i].material);
    }
    print_ambient_light(world->ambient_light);
    print_point_lights(world);
    t_vec vp = world->camera.view_point;
    t_vec dir = world->camera.direction;
    printf("\t[camera]\n\t\tviewpoint=(%f,%f,%f)\n\t\tdirection=(%f,%f,%f)\n\t\thfov=%f\n", vp.x, vp.y, vp.z, dir.x, dir.y, dir.z, world->camera.hfov);
}
