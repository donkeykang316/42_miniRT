/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:57:00 by kaan              #+#    #+#             */
/*   Updated: 2024/08/09 22:58:46 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_rt_file(char *path)
{
	int	len;

	len = ft_strlen(path) - 3;
	if (len > 3)
		return (ft_strncmp(path + len, ".rt", 3) == 0);
	return (true);
}

int file_valid(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (error_msg("Failed to open file"));
    if (!is_rt_file(file))
        return (error_msg("Invalid file extension"));
    if (read_file(fd))
        return (0);
    return (0);
}

char    *line_cleaner(char *line)
{
    int     i;

    i = 0;
    while (line[i])
    {
        if (line[i] >= 7 && line[i] <= 13)
            line[i] = 32;
        i++;
    }
    return (line); 
}

//int acl_duplitcate()

int read_file(int fd)
{
    char    *line;
    int     ret;
    int     i;

    i = 0;
    ret = 0;
    while (ret != 1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        line = line_cleaner(line);
        ret = input_valid(line);
        free(line);
        if (ret != -1)
            i++;
    }
    if (!i)
        return (error_msg("Empty file"));
    if (ret == 1)
    {
        printf("Error on line %d\n", ret);
        return (ret);
    }
    return (0);
}
