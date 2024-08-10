/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:46:17 by kaan              #+#    #+#             */
/*   Updated: 2024/08/10 13:51:57 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void    parse_line(t_parser *parser, char *line)
{
    if (ft_strncmp(line, "A", 1) == 0)
        ambient_parse(parser, line);
    else if (ft_strncmp(line, "C", 1) == 0)
        camera_parse(parser, line);
    else if (ft_strncmp(line, "L", 1) == 0)
        light_parse(parser, line);
    else if (ft_strncmp(line, "pl", 2) == 0)
        quad_parse(parser, line);
    else if (ft_strncmp(line, "tr", 2) == 0)
        tri_parse(parser, line);
    else if (ft_strncmp(line, "sp", 2) == 0)
        sphere_parse(parser, line);
    else if (ft_strncmp(line, "cy", 2) == 0)
        cylinder_parse(parser, line);
}

void    parse_input(t_parser *parser, int fd)
{
    char        *line;

    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        line = line_cleaner(line);
        parse_line(parser, line);
        free(line);
    }
}

void parsing(t_parser *parser, char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        error_msg("Failed to open file");
        exit(1);
    }
    parse_input(parser, fd);
    close(fd);
}
