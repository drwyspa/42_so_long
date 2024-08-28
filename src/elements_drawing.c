/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_drawing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 21:09:23 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/08/28 22:17:15 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Loads game textures from the files.
// param:
// - 'data' - pointer to the game data.
//
void	load_textures(t_data *data)
{
	int	width;
	int	height;

	data->textures[0] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/bg.xpm", &width, &height);
	data->textures[1] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/wall.xpm", &width, &height);
	data->textures[2] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/item.xpm", &width, &height);
	data->textures[3] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/hero.xpm", &width, &height);
	data->textures[4] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/exit.xpm", &width, &height);
	data->textures[5] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/exit_open.xpm", &width, &height);
	data->textures[6] = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/endofgame.xpm", &width, &height);
	data->textures[7] = NULL;
}

// Draws individual element odn the game window,
// by first selectet particular texture.
// params:
// - 'data' - pointer to the game data structure.
// - 'y' - y coordinate on the game map grid.
// - 'x' - x coordinate on the game map grid.
//
static void	draw_element(t_data *data, int y, int x)
{
	char	**map_grid_ptr;

	map_grid_ptr = data->map->map_grid;
	if (map_grid_ptr[y][x] == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->textures[1], x * TILE_SIZE, y * TILE_SIZE);
	else if (map_grid_ptr[y][x] == '0')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->textures[0], x * TILE_SIZE, y * TILE_SIZE);
	else if (map_grid_ptr[y][x] == 'P')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->textures[3], x * TILE_SIZE, y * TILE_SIZE);
	else if (map_grid_ptr[y][x] == 'E')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->textures[4], x * TILE_SIZE, y * TILE_SIZE);
	else if (map_grid_ptr[y][x] == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->textures[2], x * TILE_SIZE, y * TILE_SIZE);
}

// Draw static elements on the game map.
// Calls draw_element function on each map grid.
// param:
// - 'data' - pointer to the game data.
//
void	draw_static_elements(t_data *data)
{
	char	**map_grid_ptr;
	int		y;
	int		x;

	map_grid_ptr = data->map->map_grid;
	y = 0;
	while (map_grid_ptr[y])
	{
		x = 0;
		while (map_grid_ptr[y][x])
		{
			draw_element(data, y, x);
			x++;
		}
		y++;
	}
}
