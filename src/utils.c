/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:42:44 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/09/03 18:54:18 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//Clean exit the game. 
// params:
// - 'data' - game data structure.
// - 'err' - error message (defined in header file).
//
void	msg_err_and_exit(t_data *data, char *err)
{
	if (data->map->map_grid != NULL)
		free_map_grid(data);
	if (data->mlx_ptr != NULL || data->win_ptr != NULL)
	{
		free_textures(data);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

// Frees memory allocated for map storage.
// param:
// - 'data' - game data structure.
//
void	free_map_grid(t_data *data)
{
	char	**map_grid_ptr;

	map_grid_ptr = data->map->map_grid;
	while (*map_grid_ptr)
	{
		free(*map_grid_ptr);
		map_grid_ptr++;
	}
	free(data->map->map_grid);
	data->map->map_grid = NULL;
}

// Frees all the memory used for store the textures.
// param:
// - 'data' - game data structure;
//
void	free_textures(t_data *data)
{
	int	i;

	i = 0;
	while (data->textures[i])
	{
		mlx_destroy_image(data->mlx_ptr, data->textures[i]);
		i++;
	}
}
