/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:07:07 by kaan              #+#    #+#             */
/*   Updated: 2024/08/10 03:46:16 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minirt.h"

typedef struct  s_parser
{
    char            *category;
    double          *param;
    int             idx;
}   t_parser;

//parser
void parser(char *file);
void    parse_input(int fd);
void    parse_line(char *line, t_parser *parser);
void    parse_to(char *line, char *to);


//file check
int file_valid(char *file);
bool	is_rt_file(char *path);
int read_file(int fd);
char    *line_cleaner(char *line);

//file input valid 0
int	input_valid(char *line);
int	ambient_valid(char *line);
int	camera_valid(char *line);
int	light_valid(char *line);
int sphere_valid(char *line);

//file input valid 1
int plane_valid(char *line);
int cylinder_valid(char *line);

//file input util
int	doubleptr_error(char **token, char *msg);
bool	param_nbr_valid(char **token, int nbr);
int	color_valid(char *line);
int	coord_valid(char *line);
int	orien_valid(char *line);

//nbr_valid
bool    ft_isfloat(char *str);
double    ft_atof(char *str);

//parser free
void    free_double(char **double_str);

#endif