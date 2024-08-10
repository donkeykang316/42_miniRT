/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:07:07 by kaan              #+#    #+#             */
/*   Updated: 2024/08/10 15:48:26 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minirt.h"

#include "../tester.h"

typedef struct  s_amblight t_amblight;
typedef struct  s_camera t_camera;
typedef struct  s_light t_light;
typedef struct  s_object t_object;
typedef struct  s_sphere t_sphere;
typedef struct  s_quad t_quad;
typedef struct  s_triangle t_triangle;
typedef struct  s_cylinder t_cylinder;

typedef struct  s_parser
{
    t_amblight      *amblight;
    t_camera        *camera;
    t_light         *light;
    t_object        **object;
    int             object_nbr;
    int             count;
}   t_parser;

//parser
void parsing(t_parser *parser, char *file);
void    parse_input(t_parser *parser, int fd);
void    parse_line(t_parser *parser, char *line);
void    parse_to(char *line, char *to);

//parser util 0
void    ambient_parse(t_parser *parser, char  *line);
void    camera_parse(t_parser *parser, char *line);
void    light_parse(t_parser *parser, char *line);

//parser util 1
void    sphere_parse(t_parser *parser, char *line);
void    quad_parse(t_parser *parser, char *line);
void    tri_parse(t_parser *parser, char *line);
void    cylinder_parse(t_parser *parser, char *line);

//file check
int file_valid(char *file, int *nbr);
bool	is_rt_file(char *path);
int read_file(int fd, int *nbr);
char    *line_cleaner(char *line);

//file input valid 0
int	input_valid(char *line, int *nbr);
int	ambient_valid(char *line);
int	camera_valid(char *line);
int	light_valid(char *line);

//file input valid 1
int sphere_valid(char *line, int *nbr);
int plane_valid(char *line, int *nbr);
int cylinder_valid(char *line, int *nbr);

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
void    parser_free(t_parser *parser);

#endif