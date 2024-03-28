/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcodrean <vcodrean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:51:00 by arr02             #+#    #+#             */
/*   Updated: 2024/01/02 18:37:12 by vcodrean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/inc/ft_printf.h"
# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line.h"
//# include "../mlx_linux/mlx.h"
//# include "../mlx_linux/mlx_int.h"
# include "./structs.h"
# include <mlx.h>
# include <math.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

# define SCREEN_WIDTH 740
# define SCREEN_HEIGHT 520
# define RIGHT_KEY 0xFF51
# define LEFT_KEY 0xFF53
# define UP_KEY 0xFF52
# define DOWN_KEY 0xFF54
# define SCAPE_KEY 0xFF1B
# define WALLS 4
# define COLORS 2
# define WALL_SIZE 64


t_map		*load_cub3d(char *filename);
t_map		*init_map(int fd, char *filename);
t_boolean	check_color_range(int col);
t_boolean	is_map_content(char *s);
t_boolean	check_last(t_map *map);
t_boolean	is_player(char c);
t_boolean	is_info_correct(t_map *map, char *first_line);
t_boolean	content_get_lines(t_map *map);
t_boolean	check_f_l(t_map *map, char *line);
t_boolean	check_middle_line(t_map *map, char *line);
t_status	check_args(int argc, char **argv);
void        load_content(t_map *map, char *first_line);
void		free_color(void *ptr);
void		free_textures(void *ptr);
void		show_error(char *error);
void		free_all(t_map *map, char *msg, t_status st);
int			ft_split_get_length(char **s);
int			int_value(char c);
void         launch(t_map *map);
char		*load_textures(t_map *map);
void        create_img(t_map *map);
void        create_texture(t_map *map);
int	        event_handler(enum e_keys key, t_map *map);
int	        exit_game(t_map *map);
void        calculate_player_coordinates(t_map *map);
void        find_player(t_map *map);
#endif