/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cub3D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcodrean <vcodrean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:21:25 by alvarrod          #+#    #+#             */
/*   Updated: 2023/12/10 11:50:20 by vcodrean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

/**
 * @brief This function loads the map struct, 
 * calling both load_texture and load_content function
 * 
 * @param filename the filename where the map is stored
 * @return t_map* the initialized map
 */
t_map	*load_cub3d(char *filename)
{
	int		fd;
	t_map	*map;

	fd = open(filename, O_RDONLY);
	if (!fd)
		return (NULL);
	map = init_map(fd, filename);
	if (!map)
		exit(EXIT_FAILURE);
	load_content(map, load_textures(map));
	return (map);
}
