/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:59:06 by kaan              #+#    #+#             */
/*   Updated: 2024/08/10 06:31:29 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void    sphere_parse(t_parser *parser, char *line)
{
    char    **tokens;
    char    **position;
    char    **color;

    parser->object_list[parser->count] = malloc(sizeof(t_object_list));
    parser->object_list[parser->count]->sphere = malloc(sizeof(t_sphere));
    tokens = ft_split(line, ' ');
    position = ft_split(tokens[1], ',');
    parser->object_list[parser->count]->type = SPHERE;
    parser->object_list[parser->count]->sphere->center = vec_init(ft_atof(position[0]), ft_atof(position[1]), ft_atof(position[2]));
    parser->object_list[parser->count]->sphere->radius = ft_atof(tokens[2]);
    color = ft_split(tokens[3], ',');
    parser->object_list[parser->count]->sphere->material = malloc(sizeof(t_material));
    parser->object_list[parser->count]->sphere->material->albedo = vec_init(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
    color = ft_split(tokens[3], ',');
    free_double(tokens);
    free_double(position);
    free_double(color);
    parser->count += 1;
}

void    quad_parse(t_parser *parser, char *line)
{
    char    **tokens;
    char    **position;
    char    **normal;
    char    **color;

    parser->object_list[parser->count] = malloc(sizeof(t_object_list));
    parser->object_list[parser->count]->quad = malloc(sizeof(t_quad));
    tokens = ft_split(line, ' ');
    position = ft_split(tokens[1], ',');
    parser->object_list[parser->count]->type = QUAD;
    parser->object_list[parser->count]->quad->q = vec_init(ft_atof(position[0]), ft_atof(position[1]), ft_atof(position[2]));
    normal = ft_split(tokens[2], ',');
    parser->object_list[parser->count]->quad->u = vec_init(ft_atof(normal[0]), ft_atof(normal[1]), ft_atof(normal[2]));
    color = ft_split(tokens[3], ',');
    parser->object_list[parser->count]->quad->material = malloc(sizeof(t_material));
    parser->object_list[parser->count]->quad->material->albedo = vec_init(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
    free_double(tokens);
    free_double(position);
    free_double(normal);
    free_double(color);
    parser->count += 1;
}

void    tri_parse(t_parser *parser, char *line)
{
    char    **tokens;
    char    **position;
    char    **normal;
    char    **color;

    parser->object_list[parser->count] = malloc(sizeof(t_object_list));
    parser->object_list[parser->count]->tri = malloc(sizeof(t_tri));
    tokens = ft_split(line, ' ');
    position = ft_split(tokens[1], ',');
    parser->object_list[parser->count]->type = TRIANGLE;
    parser->object_list[parser->count]->tri->q = vec_init(ft_atof(position[0]), ft_atof(position[1]), ft_atof(position[2]));
    normal = ft_split(tokens[2], ',');
    parser->object_list[parser->count]->tri->u = vec_init(ft_atof(normal[0]), ft_atof(normal[1]), ft_atof(normal[2]));
    color = ft_split(tokens[3], ',');
    parser->object_list[parser->count]->tri->material = malloc(sizeof(t_material));
    parser->object_list[parser->count]->tri->material->albedo = vec_init(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
    free_double(tokens);
    free_double(position);
    free_double(normal);
    free_double(color);
    parser->count += 1;
}

void    cylinder_parse(t_parser *parser, char *line)
{
    char    **tokens;
    char    **position;
    char    **normal;
    char    **color;

    parser->object_list[parser->count] = malloc(sizeof(t_object_list));
    parser->object_list[parser->count]->cyl = malloc(sizeof(t_cylinder));
    tokens = ft_split(line, ' ');
    position = ft_split(tokens[1], ',');
    parser->object_list[parser->count]->type = CYLINDER;
    parser->object_list[parser->count]->cyl->center = vec_init(ft_atof(position[0]), ft_atof(position[1]), ft_atof(position[2]));
    normal = ft_split(tokens[2], ',');
    parser->object_list[parser->count]->cyl->axis = vec_init(ft_atof(normal[0]), ft_atof(normal[1]), ft_atof(normal[2]));
    parser->object_list[parser->count]->cyl->radius = ft_atof(tokens[3]);
    parser->object_list[parser->count]->cyl->height = ft_atof(tokens[4]);
    color = ft_split(tokens[5], ',');
    parser->object_list[parser->count]->cyl->material = malloc(sizeof(t_material));
    parser->object_list[parser->count]->cyl->material->albedo = vec_init(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
    free_double(tokens);
    free_double(position);
    free_double(normal);
    free_double(color);
    parser->count += 1;
}