/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcodrean <vcodrean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:24:39 by alvarrod          #+#    #+#             */
/*   Updated: 2023/12/18 19:23:07 by vcodrean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/* Enumerando las teclas*/
typedef enum e_keys
{
	W_ON = 13,
	A_ON = 0,
	S_ON = 1,
	DD = 2,
	UP = 126,
	LEFT = 123,
	DOWN = 125,
	RIGHT = 124,
	ESC = 53,
	DESTROY = 17
	
} t_keys;
/**
 * @brief Enumerado para saber si es un techo o un suelo
 * o está sin inicializar
 * 
 */
typedef enum e_celfloor{
	NONE_CEL = -1,
	C = 0,
	F = 1
}	t_celfloor;

/**
 * @brief Enumerado para saber el tipo de textura
 * o si no está inicializada
 * 
 */
typedef enum e_cardinal{
	NONE_CAR = -1,
	SO = 0,
	NO = 1,
	EA = 2,
	WE = 3
}	t_cardinal;

/**
 * @brief Enumerado para saber si una celda se trata
 * de un muro o de un espacio vacio
 * 
 */
typedef enum e_type_of_elem{
	EMPTY = 4,
	WALL = 5
}	t_type_of_elem;

/**
 * @brief Enumerado para saber hacia donde mira un jugador
 * 
 */
typedef enum e_player_cardinal{
	S = 0,
	N = 1,
	E = 2,
	W = 3
}	t_player_cardinal;

/**
 * @brief Enumerado para organizar los colores
 * 
 */
typedef enum e_rgb{
	R,
	G,
	B
}	t_rgb;

/**
 * @brief Estructura que almacena 
 * un tipo de pared de muro con el 
 * fichero que sirve para mostrarla
 * 
 */


/**
 * @brief Estructura que relaciona un enumerado t_rgb con
 * su valor correspondiente
 * asi podríamos tener algo como R = 185
 * 
 */
typedef struct s_color_value
{
	t_rgb	color;
	int		value;
}	t_color_value;

/**
 * @brief Estructura que almacena el si es un techo o un suelo
 * y para cada uno de estos almacenará 3 colores con 3 valores
 * de entre 0 y 255
 * 
 */
typedef struct s_colors
{
	t_celfloor		celflor;
	t_color_value	*color;
}	t_color;

/**
 * @brief Estructura que sirve para almacenar el contenido del mapa
 * Almacena, un doble puntero que tendrá el mapa,
 * Un entero con el número total de lineas que debería de tener
 * Un entero con el número total de lineas almacenadas hasta el momento
 * Un booleano que indica si se ha definido o no un jugador
 * 
 */
typedef struct s_content
{
	int			**map_content;
	int			map_lines;
	int			defined_lines;
	t_boolean	player;
}	t_content;

/**
 * @brief Estructura que almacena todos los datos necesarios para
 * la representación del mapa, almacena un file descriptor del mapa,
 * el filename del mapa por si en algún momento se cierra,
 * Las texturas del mapa, Los colores del mapa y por último el contenido del mapa
 * 
 */

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	
	float	x;
	float	y;
	float	old_x;
	float	old_y;
	float	cam;
	t_vector	dir;
	
}	t_player;


typedef struct s_camera
{
	t_vector	plane;
	int			grid_x;
	int			grid_y;
	
}	t_camera;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		height;
	int		width;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_textures
{
	t_cardinal	cardinal;
	t_img		img;
	int			*txt_values;
	char		*texture;

}	t_textures;

typedef struct s_map
{
	int			map_fd;
	char		*filename;
	char		*txt_map_no;
	char		*txt_map_so;
	char		*txt_map_we;
	char		*txt_map_ea;
	void		*mlx;
	void		*mlx_win;
	char 		**map;
	t_img 		img;
	t_textures 	txt_no;
	t_textures 	txt_so;
	t_textures 	txt_we;
	t_textures 	txt_ea;
	t_player	player;
	t_camera	cam;
	t_textures	**texture_packs;
	t_color		**color_packs;
	t_content	content;
}	t_map;
#endif
