/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvarrod <a.rr02_cuentas@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:21:28 by alvarrod          #+#    #+#             */
/*   Updated: 2023/11/08 20:52:00 by alvarrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

/**
 * @brief This function is used to stored the read line inside our map
 * 
 * @param map the map where the line will be stored
 * @param line the line that will be stored
 * @return t_boolean checks if the storing was correct or not
 */
t_boolean	store_line(t_map *map, char *line)
{
	int	i;

	i = 0;
	map->content.map_content[map->content.defined_lines] = \
	(int *) malloc(sizeof(int) * (ft_strlen(line) + 1));
	if (!map->content.map_content)
		return (FALSE);
	while (line[i])
	{
		if (is_player(line[i]))
		{
			if (map->content.player)
			{
				return (FALSE);
			}
			map->content.player = TRUE;
		}
		map->content.map_content[map->content.defined_lines][i] = \
		int_value(line[i]);
		i++;
	}
	map->content.map_content[map->content.defined_lines][i] = -1;
	map->content.defined_lines++;
	return (TRUE);
}

/**
 * @brief This function is used to check either the 
 * first and las lines where correct and calls the storing function
 * 
 * @param map the map where the line will be stored
 * @param line the line that will be stored
 * @return t_boolean to check if the storing was correct
 */
t_boolean	check_middle_line(t_map *map, char *line)
{
	int	i;

	(void) map;
	if (!line)
		return (TRUE);
	i = 0;
	ft_rm_char_from_str(line, ' ');
	ft_rm_char_from_str(line, '\n');
	if (ft_strlen(line) == 0)
		return (FALSE);
	if (line[0] != '1' || line[ft_strlen(line) - 1] != '1')
		return (FALSE);
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && !is_player(line[i]))
			return (FALSE);
		i++;
	}
	return (store_line(map, line));
}

/**
 * @brief Used to check first and last line and calls the store function
 *  
 * @param map The map where we will store the line
 * @param line the line that will be stored
 * @return t_boolean to check if the storing was correct
 */
t_boolean	check_f_l(t_map *map, char *line)
{
	int	i;

	(void) map;
	if (!line)
		return (TRUE);
	i = 0;
	ft_rm_char_from_str(line, ' ');
	ft_rm_char_from_str(line, '\n');
	if (ft_strlen(line) == 0)
		return (FALSE);
	while (line[i])
	{
		if (line[i] != '1')
			return (FALSE);
		i++;
	}
	return (store_line(map, line));
}

/**
 * @brief This function counts the length of the map so it can be used later
 * 
 * @param map Where the length will be stored
 * @return t_boolean to check if the storing was correct
 */
t_boolean	content_get_lines(t_map *map)
{
	char	*line;

	map->content.map_lines = 1;
	line = get_next_line(map->map_fd);
	while (line)
	{
		map->content.map_lines++;
		free(line);
		line = get_next_line(map->map_fd);
	}
	close(map->map_fd);
	map->map_fd = open(map->filename, O_RDONLY);
	map->content.map_content = (int **) malloc(sizeof(int *) \
	* map->content.map_lines);
	if (!map->content.map_content || map->map_fd == -1)
		return (FALSE);
	line = get_next_line(map->map_fd);
	while (is_map_content(line) == FALSE)
	{
		free(line);
		line = get_next_line(map->map_fd);
	}
	free(line);
	return (TRUE);
}

/**
 * @brief loads the content of the map
 * 
 * @param map where the map is gonna be stored
 * @param first_line the first line that will be proccessed
 * @return t_status the status of the load
 */
void	load_content(t_map *map, char *first_line)
{
	char		*line;

	if (is_info_correct(map, first_line) == FALSE)
		free_all(map, "Error loading textures of map", INPUT_DATA_FORMAT_ERROR);
	line = first_line;
	while (line)
	{
		free(line);
		line = get_next_line(map->map_fd);
		if (!line)
			break ;
		if (check_middle_line(map, line) == FALSE)
		{
			free(line);
			free_all(map, "Error loading textures of map", \
			INPUT_DATA_FORMAT_ERROR);
		}
	}
	if (check_last(map) == FALSE)
		free_all(map, "Error loading of map", INPUT_DATA_FORMAT_ERROR);
}
