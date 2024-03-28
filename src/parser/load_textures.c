/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcodrean <vcodrean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:05:44 by alvarrod          #+#    #+#             */
/*   Updated: 2023/12/10 11:52:05 by vcodrean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

/**
 * @brief stored the ceiling and floor of the map
 * checks if the color is correct and between the correct range
 * 
 * @param map the map where the info will be stored
 * @param text the color
 * @param celflor represents the ceiling or the floor
 * @return t_status BASIC ERROR HANDLING
 */
t_status	check_color(t_map *map, char *text, t_celfloor celflor)
{
	char	**sp;

	if (map->color_packs[celflor]->celflor != NONE_CEL)
		return (INPUT_DATA_FORMAT_ERROR);
	sp = ft_split(text, ',');
	if (!sp)
		return (MALLOC_ERROR);
	if ((!ft_strisdigit(sp[0]) || !ft_strisdigit(sp[1]) \
	|| !ft_strisdigit(sp[2])) || ft_strarr_len(sp) != 3)
	{
		ft_free_double_void_pointer((void **)sp, ft_strarr_len(sp), free);
		return (INPUT_DATA_FORMAT_ERROR);
	}
	map->color_packs[celflor]->celflor = celflor;
	map->color_packs[celflor]->color[R].value = ft_atoi(sp[0]);
	map->color_packs[celflor]->color[G].value = ft_atoi(sp[1]);
	map->color_packs[celflor]->color[B].value = ft_atoi(sp[2]);
	ft_free_double_void_pointer((void **)sp, ft_strarr_len(sp), free);
	if ((!check_color_range(map->color_packs[celflor]->color[R].value)) || \
	(!check_color_range(map->color_packs[celflor]->color[G].value)) || \
	(!check_color_range(map->color_packs[celflor]->color[B].value)))
		return (INPUT_DATA_FORMAT_ERROR);
	return (SUCCESS);
}

/**
 * @brief checks if a texture is correct and the file of the texture exists
 * copies the information into the map place
 * 
 * @param map the map where the info will be stored
 * @param text the text containing the filename
 * @param card the cardinal it represents
 * @return t_status BASIC ERROR HANDLING
 */
t_status	check_texture(t_map *map, char *text, t_cardinal card)
{
	int	fd;

	if (map->texture_packs[card]->cardinal != NONE_CAR)
		return (INPUT_DATA_FORMAT_ERROR);
	text[ft_strlen(text) - 1] = 0;
	fd = open(text, O_RDONLY);
	if (fd == -1)
		return (FILE_NOT_FOUND);
	close(fd);
	map->texture_packs[card]->cardinal = card;
	map->texture_packs[card]->texture = (char *) malloc(sizeof(char) \
	* ft_strlen(text) + 1);
	if (!map->texture_packs[card]->texture)
		return (MALLOC_ERROR);
	ft_strncpy(map->texture_packs[card]->texture, text+2, ft_strlen(text)-2);
	//map->texture_packs[card]->texture[ft_strlen(text) - 2] = '\0';
	return (SUCCESS);
}

/**
 * @brief proccesses the text to see if its a color or a texture
 * and calls the checking function
 * 
 * @param map where the texture or color will be estored
 * @param text the read line
 * @return t_status BASIC ERROR HANDLING
 */
t_status	process_texture(t_map *map, char **text)
{
	if (ft_strlen(text[0]) == 1)
	{
		if (text[0][0] == 'C')
			return (check_color(map, text[1], C));
		else if (text[0][0] == 'F')
			return (check_color(map, text[1], F));
		else
			return (INPUT_DATA_FORMAT_ERROR);
	}
	else if (ft_strlen(text[0]) == 2)
	{
		if (text[0][0] == 'S' && text[0][1] == 'O')
			return (check_texture(map, text[1], SO));
		else if (text[0][0] == 'W' && text[0][1] == 'E')
			return (check_texture(map, text[1], WE));
		else if (text[0][0] == 'E' && text[0][1] == 'A')
			return (check_texture(map, text[1], EA));
		else if (text[0][0] == 'N' && text[0][1] == 'O')
			return (check_texture(map, text[1], NO));
		else
			return (INPUT_DATA_FORMAT_ERROR);
	}
	return (INPUT_DATA_FORMAT_ERROR);
}

/**
 * @brief reads one line of the file and calls the funcion to process that line
 * 
 * @param map where the texture is gonna be stored
 * @param line the line that contains the texture
 * @return t_status BASIC ERROR HANDLING
 */
t_status	get_texture(t_map *map, char *line)
{
	char	**sp;

	if (!line)
		return (GENERAL_ERROR);
	if (ft_strlen(line) == 0)
		return (SUCCESS);
	if (line[0] == '\n')
		return (SUCCESS);
	sp = ft_split(line, ' ');
	if (!sp)
		return (MALLOC_ERROR);
	if (process_texture(map, sp) || ft_strarr_len(sp) != 2)
	{
		ft_free_double_void_pointer((void **) sp, ft_strarr_len(sp), free);
		return (INPUT_DATA_FORMAT_ERROR);
	}
	ft_free_double_void_pointer((void **) sp, ft_strarr_len(sp), free);
	return (SUCCESS);
}

/**
 * @brief The main function to load textures
 * it calls the needed functions and make error checking
 * 
 * @param map where the map textures are gonna be stored
 * @return char* the first line of the map
 */
char	*load_textures(t_map *map)
{
	char		*line;
	t_status	st;

	line = get_next_line(map->map_fd);
	while (is_map_content(line) == FALSE)
	{
		st = get_texture(map, line);
		free(line);
		if (st > 0)
			free_all(map, "Error loading textures of map", st);
		line = get_next_line(map->map_fd);
	}
	return (line);
}
