/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvarrod <a.rr02_cuentas@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:09:30 by alvarrod          #+#    #+#             */
/*   Updated: 2023/11/08 20:26:45 by alvarrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

/**
 * @brief Makes the last checking to the map,
 * checks if there is a player and if the last line was correctly formatted
 * 
 * @param map the map to check
 * @return t_boolean the check result
 */
t_boolean	check_last(t_map *map)
{
	int	i;
	int	*line;

	if (map->content.player == FALSE)
		return (FALSE);
	i = 0;
	line = map->content.map_content[map->content.defined_lines - 1];
	while (line[i] != -1)
	{
		if (line[i] != WALL)
			return (FALSE);
		i++;
	}
	if (i == 0)
		return (FALSE);
	return (TRUE);
}

/**
 * @brief checks if its a player
 * 
 * @param c the char to check
 * @return t_boolean TRUE or FALSE depending if its a player or not
 */
t_boolean	is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (TRUE);
	return (FALSE);
}

/**
 * @brief Makes a conversion c to its numeric value
 * 
 * @param c the char to convert
 * @return int the new value
 */
int	int_value(char c)
{
	if (c == 'S')
		return (S);
	else if (c == 'N')
		return (N);
	else if (c == 'E')
		return (E);
	else if (c == 'W')
		return (W);
	else if (c == '0')
		return (EMPTY);
	else
		return (WALL);
}

/**
 * @brief checks if the textures and colors are correctly
 * stored, gets the length of the upcoming map and stores the first line
 * 
 * @param map the map to check
 * @param first_line the first line of the map
 * @return t_boolean used to check if the function was executed correctly
 */
t_boolean	is_info_correct(t_map *map, char *first_line)
{
	if (map->color_packs[0]->celflor == NONE_CEL)
		return (FALSE);
	if (map->color_packs[1]->celflor == NONE_CEL)
		return (FALSE);
	if (map->texture_packs[0]->cardinal == NONE_CAR)
		return (FALSE);
	if (map->texture_packs[1]->cardinal == NONE_CAR)
		return (FALSE);
	if (map->texture_packs[2]->cardinal == NONE_CAR)
		return (FALSE);
	if (map->texture_packs[3]->cardinal == NONE_CAR)
		return (FALSE);
	if (content_get_lines(map) == FALSE)
	{
		free(first_line);
		free_all(map, "Error in map content", INPUT_DATA_FORMAT_ERROR);
	}
	if (check_f_l(map, first_line) == FALSE)
	{
		free(first_line);
		free_all(map, "Error in map content", INPUT_DATA_FORMAT_ERROR);
	}
	return (TRUE);
}
