/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:50:32 by kaan              #+#    #+#             */
/*   Updated: 2024/08/08 20:35:40 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int open_file(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (error_msg("Failed to open file"));
    if (!is_rt_file(file))
        return (error_msg("Invalid file extension"));
    if (read_file(fd))
        return (0);
    return (1);
}

char    *line_cleaner(char *line)
{
    char    *cleaned;
    int     i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
        i++;
    if (line[i] == '\0')
        return (NULL);
    cleaned = malloc(ft_strlen(line) - i + 1);
    ft_strlcpy(cleaned, line, ft_strlen(line) - i + 1);
    free(line);
    return (cleaned);
}

int read_file(int fd)
{
    char    *line;
    int     ret;
    int     i;

    i = 0;
    while (ret != 1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        line = line_cleaner(line);
        if (!line)
            continue ;
        ret = parser(line);
        free(line);
        i++;
    }
    if (!i)
        return (error_msg("Empty file"));
    return (0);
}