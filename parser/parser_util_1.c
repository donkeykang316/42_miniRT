/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:59:06 by kaan              #+#    #+#             */
/*   Updated: 2024/08/10 15:49:40 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void    sphere_parse(t_parser *parser, char *line)
{
    char    **tokens;
    char    **position;
    char    **color;

    tokens = ft_split(line, ' ');
    position = ft_split(tokens[1], ',');
    parser->object[parser->count]->type = SPHERE;
    parser->object[parser->count]->value.sphere.center = vec_init(ft_atof(position[0]), ft_atof(position[1]), ft_atof(position[2]));
    parser->object[parser->count]->value.sphere.radius = ft_atof(tokens[2]);
    color = ft_split(tokens[3], ',');
    parser->object[parser->count]->material.type = LAMBERTIAN;
    parser->object[parser->count]->material.albedo = vec_init(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
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

    tokens = ft_split(line, ' ');
    position = ft_split(tokens[1], ',');
    parser->object[parser->count]->type = QUAD;
    parser->object[parser->count]->value.quad.q = vec_init(ft_atof(position[0]), ft_atof(position[1]), ft_atof(position[2]));
    normal = ft_split(tokens[2], ',');
    parser->object[parser->count]->value.quad.u = vec_init(ft_atof(normal[0]), ft_atof(normal[1]), ft_atof(normal[2]));
    color = ft_split(tokens[3], ',');
    parser->object[parser->count]->material.type = LAMBERTIAN;
    parser->object[parser->count]->material.albedo = vec_init(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
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

    tokens = ft_split(line, ' ');
    position = ft_split(tokens[1], ',');
    parser->object[parser->count]->type = TRIANGLE;
    parser->object[parser->count]->value.triangle.q = vec_init(ft_atof(position[0]), ft_atof(position[1]), ft_atof(position[2]));
    normal = ft_split(tokens[2], ',');
    parser->object[parser->count]->value.triangle.u = vec_init(ft_atof(normal[0]), ft_atof(normal[1]), ft_atof(normal[2]));
    color = ft_split(tokens[3], ',');
    parser->object[parser->count]->material.type = LAMBERTIAN;
    parser->object[parser->count]->material.albedo = vec_init(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
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

    tokens = ft_split(line, ' ');
    position = ft_split(tokens[1], ',');
    parser->object[parser->count]->type = CYLINDER;
    parser->object[parser->count]->value.cyllinder.center = vec_init(ft_atof(position[0]), ft_atof(position[1]), ft_atof(position[2]));
    normal = ft_split(tokens[2], ',');
    parser->object[parser->count]->value.cyllinder.axis = vec_init(ft_atof(normal[0]), ft_atof(normal[1]), ft_atof(normal[2]));
    parser->object[parser->count]->value.cyllinder.radius = ft_atof(tokens[3]);
    parser->object[parser->count]->value.cyllinder.height = ft_atof(tokens[4]);
    color = ft_split(tokens[5], ',');
    parser->object[parser->count]->material.type = LAMBERTIAN;
    parser->object[parser->count]->material.albedo = vec_init(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
    free_double(tokens);
    free_double(position);
    free_double(normal);
    free_double(color);
    parser->count += 1;
}