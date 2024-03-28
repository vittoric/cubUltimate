/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcodrean <vcodrean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:34:40 by alvarrod          #+#    #+#             */
/*   Updated: 2024/03/28 11:57:14 by vcodrean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

/**
 * @brief checks if a color is between the correct range
 * 
 * @param col the color
 * @return t_boolean TRUE or FALSE
 */
t_boolean	check_color_range(int col)
{
	if (col < 0 || col > 255)
		return (FALSE);
	return (TRUE);
}

/**
 * @brief checks if a line is part of the content of the map
 * 
 * @param s the line
 * @return t_boolean TRUE or FALSE
 */
t_boolean	is_map_content(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (FALSE);
	if (ft_strlen(s) == 0)
		return (FALSE);
	while ((ft_isspace(s[i])) && s[i])
		i++;
	if (s[i] == '1' || s[i] == '0')
		return (TRUE);
	return (FALSE);
}

/**
 * @brief checks number of args and if the last arg ends in .cub
 * 
 * @param argc number of args
 * @param argv the arguments
 * @return t_status 
 */
t_status	check_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		return (GENERAL_ERROR);
	len = ft_strlen(argv[1]);
	if (argv[1][len - 1] != 'b' || argv[1][len - 2] != 'u' \
	|| argv[1][len - 3] != 'c' || argv[1][len - 4] != '.')
		return (INPUT_DATA_FORMAT_ERROR);
	return (SUCCESS);
}



void calculate_player_coordinates(t_map *map)
{
    int i, j;
    int **map_content = map->content.map_content;

    i = 0;
    while (i < map->content.map_lines)
    {
        j = 0;
        while (map_content[i][j] != -1)
        {
            if (map_content[i][j] == (int)map->player.dir.x && map_content[i][j + 1] == (int)map->player.dir.y)
            {
                map->player.x = j;
                map->player.y = i;
                return;
            }
            j++;
        }
        i++;
    }
}
