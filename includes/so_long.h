/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 21:07:21 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/09/16 20:41:42 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../mlx/mlx.h"

# define SUCCESS 0
# define FAIL -1

# define BUFFER_SIZE 4096
# define TILE_SIZE 64
# define GAME_TITLE "Goblins mine"

//Error definition.
//This way we don't have to use ft_printf. 
//We can use write function instead.
//The whole code will be simplier.
//
# define ERR_MALLOC "Error - memory allocation failed"
# define ERR_FILE "Error - open or read file failure"
# define ERR_NO_FILE_PATH "Error - wrong path to map file"
# define ERR_NO_RECT "Error - your map should be a rectangle"
# define ERR_NO_ITEMS "Error - missing player position or collectibles"
# define ERR_UNDEF_ITEM "Error - undefined element on the map"
# define ERR_NOT_CLOSED "Error - check the map borders"
# define ERR_NO_PATH "Error - missing correct path between items and exit"
# define ERR_MLX "Error - MLX initialization fail"
# define ERR_MLX_WIN "Error - MLX - window creation fail"
# define ERR_EMPTY_ROW "Error - no empty rows please"

typedef struct t_point
{
	int	x;
	int	y;
}	t_point;

typedef struct t_map
{
	char	**map_grid;
	int		width;
	int		height;
	int		coll_cnt;
	int		player_moves_cnt;
	t_point	player_pos;
	t_point	exit_pos;
	int		game_finished;
}	t_map;

typedef struct t_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*textures[8];
	t_map	*map;
}	t_data;

typedef struct t_point_data
{
	t_point	new_pnt_dir[4];
	t_point	*visited_pnts;
	size_t	v_pnt_size;
	int		path_exists_flg;
}	t_point_data;

//Main module
int		on_destroy(t_data *data);

//Map validation
void	process_and_validate_map(t_data *data);

//Path validation
int		check_if_all_objects_are_reachable(t_data *data);

//Elements drawing
void	load_textures(t_data *data);
void	draw_static_elements(t_data *data);

//Movement handling
int		on_keypress(int keysym, t_data *data);

//ft_split
char	**ft_split(const char *s, char c);

//Utils
void	msg_err_and_exit(t_data *data, char *err);
void	free_map_grid(t_data *data);
void	free_textures(t_data *data);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);

//Path utils
int		pnt_already_visited(t_point_data *pnt_data, t_point now_pnt);
void	check_path_to_exit(char **map_grid_ptr,
			t_point_data *pnt_data, t_point now_pnt);
void	check_path_from_coll(char **map_grid_ptr,
			t_point_data *pnt_data, t_point now_pnt);

#endif