/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:00:06 by kaan              #+#    #+#             */
/*   Updated: 2024/08/08 19:12:22 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_rt_file(char *path)
{
	int	len;

	len = ft_strlen(path) - 3;
	if (len > 3)
		return (ft_strncmp(path + len, ".rt", 3) == 0);
	return (0);
}
