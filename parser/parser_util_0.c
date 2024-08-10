/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:58:29 by kaan              #+#    #+#             */
/*   Updated: 2024/08/10 06:26:14 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void    ambient_parse(t_parser *parser, char  *line)
{
    char        **token;
    char        **vector;

    token = ft_split(line, ' ');
    parser->amblight = malloc(sizeof(t_amblight));
    parser->amblight->intensity = ft_atof(token[1]);
    vector = ft_split(token[2], ',');
    parser->amblight->color = vec_init(ft_atof(vector[0]), ft_atof(vector[1]), ft_atof(vector[2]));
    free_double(vector);
    free_double(token);
}

void    camera_parse(t_parser *parser, char *line)
{
    char        **token;
    char        **position;
    char        **orientation;

    token = ft_split(line, ' ');
    parser->camera = malloc(sizeof(t_camera));
    position = ft_split(token[1], ',');
    parser->camera->lookat = vec_init(ft_atof(position[0]), ft_atof(position[1]), ft_atof(position[2]));
    orientation = ft_split(token[2], ',');
    parser->camera->lookfrom = vec_init(ft_atof(orientation[0]), ft_atof(orientation[1]), ft_atof(orientation[2]));
    parser->camera->vfov = ft_atof(token[3]);
    free_double(position);
    free_double(orientation);
    free_double(token);
}

void    light_parse(t_parser *parser, char *line)
{
    char        **token;
    char        **position;
    char        **color;

    token = ft_split(line, ' ');
    parser->light = malloc(sizeof(t_light));
    position = ft_split(token[1], ',');
    parser->light->position = vec_init(ft_atof(position[0]), ft_atof(position[1]), ft_atof(position[2]));
    parser->light->intensity = ft_atof(token[2]);
    color = ft_split(token[3], ',');
    parser->light->albedo = vec_init(ft_atof(color[0]), ft_atof(color[1]), ft_atof(color[2]));
    free_double(position);
    free_double(color);
    free_double(token);
}
