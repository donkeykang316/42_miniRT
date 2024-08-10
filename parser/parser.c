/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:46:17 by kaan              #+#    #+#             */
/*   Updated: 2024/08/10 03:45:21 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void    ambient_parse(t_parser *parser, char  *line)
{
    char        **token;
    char        **vector;
    int         i;

    i = 0;
    token = ft_split(line, ' ');
    parser->category = ft_strdup("Ambient");
    parser->param[0] = ft_atof(token[1]);
    vector = ft_split(token[2], ',');
    while (vector[i])
    {
        parser->param[i + 1] = ft_atof(vector[i]);
        i++;
    }
    free_double(vector);
    free_double(token);
}



void    parse_line(char *line, t_parser *parser)
{
    if (ft_strncmp(line, "A", 1) == 0)
        ambient_parse(parser, line);
    else if (ft_strncmp(line, "C", 1) == 0)
        camera_parse(parser, line);
    else if (ft_strncmp(line, "L", 1) == 0)
        light_parse(parser, line);
    else if (ft_strncmp(line, "pl", 2) == 0)
        plane_parse(parser, line);
    else if (ft_strncmp(line, "tr", 2) == 0)
        triangle_parse(parser, line);
    else if (ft_strncmp(line, "sp", 2) == 0)
        sphere_parse(parser, line);
    else if (ft_strncmp(line, "cy", 2) == 0)
        cylinder_parse(parser, line);
}

void    parse_input(int fd)
{
    t_parser    *parser;
    char        *line;

    parser = malloc(sizeof(t_parser));
    parser->idx = 0;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        line = line_cleaner(line);
        parse_line(line, parser);
        free(line);
    }
}

void parser(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        error_msg("Failed to open file");
        exit(1);
    }
    parse_input(fd);
    close(fd);
}
