/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:07:07 by kaan              #+#    #+#             */
/*   Updated: 2024/08/08 19:29:03 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minirt.h"

//parser
int    parser(char *line);

//parser util
int open_file(char *file);
int read_file(int fd);

//file check
int	is_rt_file(char *path);

#endif