#include "minirt.h"

void print_material(t_material material) {
    t_vector c = material.albedo;
    printf("\t\t\t[material]\n\t\t\t\ttype=%d\n\t\t\t\talbedo=(%.2f,%.2f,%.2f)\n", material.type, c.x, c.y, c.z);
    printf("\t\t\t\tfuzz=%f\n\t\t\t\tref_idx=%f\n", material.fuzz, material.ref_idx);
}

void print_sphere(t_object sphere) {
    t_vector center = sphere.value.sphere.center;
    printf("\t\t[sphere]\n\t\t\tcenter=(%.2f, %.2f, %.2f)\n\t\t\tradius=%f\n", center.x, center.y, center.z, sphere.value.sphere.radius);
}

void print_cylinder(t_object cylinder) {
    t_vector center = cylinder.value.cyllinder.center;
    t_vector axis = cylinder.value.cyllinder.axis;
    printf("\t\t[cylinder]\n\t\t\tcenter=(%.2f, %.2f, %.2f)\n\t\t\taxis=(%.2f, %.2f, %.2f)\n", 
        center.x, center.y, center.z, axis.x, axis.y, axis.z);
}

void print_world(t_world* world) {
    printf("[world]\n\t[objects]\n");
    for(int i = 0; i < world->objects_len; i++) {
        if (world->objects[i].type == SPHERE)
            print_sphere(world->objects[i]);
        else if (world->objects[i].type == CYLINDER)
            print_cylinder(world->objects[i]);
        else 
            printf("\t\t[unknown]\n");
        print_material(world->objects[i].material);
    }
}