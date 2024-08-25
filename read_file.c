/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:40:08 by kaan              #+#    #+#             */
/*   Updated: 2024/08/25 18:40:44 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	open_file_and_init(t_readtmp *tmp, char *name)
{
	tmp->fd = open(name, O_RDONLY, 0666);
	if (tmp->fd < 0)
		return (0);
	tmp->len = 0;
	tmp->cap = 1024;
	tmp->res = ft_calloc(tmp->cap, sizeof(char));
	if (!tmp->res)
	{
		close(tmp->fd);
		return (0);
	}
	return (1);
}

int	expand_buffer(t_readtmp *tmp)
{
	tmp->newres = ft_calloc(tmp->cap * 2, sizeof(char));
	if (!tmp->newres)
		return (0);
	ft_memcpy(tmp->newres, tmp->res, tmp->cap);
	free(tmp->res);
	tmp->res = tmp->newres;
	tmp->cap *= 2;
	return (1);
}

int	read_file_content(t_readtmp *tmp)
{
	while (1)
	{
		tmp->rd = read(tmp->fd, &tmp->res[tmp->len], tmp->cap - tmp->len);
		if (tmp->rd < 0)
			return (0);
		if (tmp->rd == 0)
			break ;
		tmp->len += tmp->rd;
		if (tmp->len == tmp->cap && !expand_buffer(tmp))
			return (0);
	}
	return (1);
}

void	cleanup_on_error(t_readtmp *tmp)
{
	if (tmp->res)
		free(tmp->res);
	if (tmp->fd >= 0)
		close(tmp->fd);
}

char	*read_file(char *name)
{
	t_readtmp	tmp;

	if (!open_file_and_init(&tmp, name))
		return (0);
	if (!read_file_content(&tmp))
	{
		cleanup_on_error(&tmp);
		return (0);
	}
	close(tmp.fd);
	return (tmp.res);
}
