/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcodrean <vcodrean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 02:12:06 by alvarrod          #+#    #+#             */
/*   Updated: 2024/03/28 11:58:11 by vcodrean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	exit_game(t_map *map)
{
	mlx_clear_window(map->mlx, map->mlx_win);
	mlx_destroy_window(map->mlx, map->mlx_win);
	exit(0);
}


void add_textures(t_map *map)
{
	map->txt_ea.txt_values = (int *)mlx_get_data_addr(map->txt_ea.img.img, &map->txt_ea.img.bits_per_pixel, &map->txt_ea.img.line_length, &map->txt_ea.img.endian);
	map->txt_we.txt_values = (int *)mlx_get_data_addr(map->txt_we.img.img, &map->txt_we.img.bits_per_pixel, &map->txt_we.img.line_length, &map->txt_we.img.endian);
	map->txt_no.txt_values = (int *)mlx_get_data_addr(map->txt_no.img.img, &map->txt_no.img.bits_per_pixel, &map->txt_no.img.line_length, &map->txt_no.img.endian);
	map->txt_so.txt_values = (int *)mlx_get_data_addr(map->txt_so.img.img, &map->txt_so.img.bits_per_pixel, &map->txt_so.img.line_length, &map->txt_so.img.endian);
}

void create_texture(t_map *map)
{
	
	map->txt_ea.img.img = mlx_xpm_file_to_image(map->mlx, map->texture_packs[EA]->texture, &map->txt_ea.img.width, &map->txt_ea.img.height);
	map->txt_we.img.img = mlx_xpm_file_to_image(map->mlx, map->texture_packs[WE]->texture, &map->txt_we.img.width, &map->txt_we.img.height);
	map->txt_no.img.img = mlx_xpm_file_to_image(map->mlx, map->texture_packs[NO]->texture, &map->txt_no.img.width, &map->txt_no.img.height);
	map->txt_so.img.img = mlx_xpm_file_to_image(map->mlx, map->texture_packs[SO]->texture, &map->txt_so.img.width, &map->txt_so.img.height);
	if(!map->txt_ea.img.img  || !map->txt_we.img.img || !map->txt_no.img.img || !map->txt_so.img.img)
	{
		printf("Error\nTexture not found");
		exit(1);		
	}
	printf("img_with: \n%d\n", map->txt_ea.img.width);
	add_textures(map);
}
/*
inicializa la estructura de imagen (map->img) creando una nueva imagen 
con dimensiones específicas y almacenando la información relevante 
sobre esa imagen en la estructura para su uso posterior
*/
void create_img(t_map *map)
{
	
	map->img.img = mlx_new_image(map->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	map->img.addr = mlx_get_data_addr(map->img.img, \
	&map->img.bits_per_pixel, &map->img.line_length, &map->img.endian);
}

void player_location(t_map *map)
{
	printf("map-player = %f\n", map->player.x);
	if (map->player.x == 0 && map->player.y == 0)
	{
		printf("Error\nPlayer not found");
		exit(1);
	}
}
void launch(t_map *map)
{
	map->mlx = mlx_init();
   	map->mlx_win = mlx_new_window(map->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	
//	printf("BBBB%s", map->texture_packs[NO]->texture);
	create_img(map); //crea la imagen
	create_texture(map); //crea las texturas
	  /*printf("Contenido de la línea %d:\n", 1);
    for (int i = 0; map->content.map_content[11][i] != -1; ++i) {
        printf("%d ", map->content.map_content[11][i]);
    }*/
	//player_location(map);
	printf("Coordenadas iniciales del jugador: (%.2f, %.2f)\n", map->player.x, map->player.y);
	mlx_hook(map->mlx_win, DESTROY, 0, exit_game, map);
	mlx_hook(map->mlx_win, 2, 1L << 0, event_handler, map);
	mlx_loop(map->mlx);
}