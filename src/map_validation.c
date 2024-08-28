/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:56:31 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/08/20 22:05:29 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Checks if the map is rectangle.
// param:
// - 'data' - game data (with the map).
//
static int	check_if_map_is_rectangle(t_data *data)
{
	char	**map_grid_ptr;

	map_grid_ptr = data->map->map_grid;
	while (*map_grid_ptr)
	{
		if (ft_strlen(*map_grid_ptr) != (size_t)data->map->width)
			return (FAIL);
		map_grid_ptr++;
	}
	return (SUCCESS);
}

// Checks if map is closed - all walls are correct :)
// param:
// - 'data' - game data.
//
static int	check_if_map_is_closed(t_data *data)
{
	char	**map_grid;
	char	*char_ptr;

	map_grid = data->map->map_grid;
	char_ptr = map_grid[0];
	while (*char_ptr != '\0')
	{
		if (*char_ptr != '1')
			return (FAIL);
		char_ptr++;
	}
	char_ptr = map_grid[data->map->height - 1];
	while (*char_ptr != '\0')
	{
		if (*char_ptr != '1')
			return (FAIL);
		char_ptr++;
	}
	while (*map_grid != NULL)
	{
		if ((*map_grid)[0] != '1' || (*map_grid)[data->map->width - 1] != '1')
			return (FAIL);
		map_grid++;
	}
	return (SUCCESS);
}

// Check if they are specific object on the map,
// and the number of them.
// They need at leas one collectable, exact one player and one exit.
// param:
// - 'data' - game data.
//
static int	check_objects(t_data *data)
{
	char	**map_grid_ptr;
	char	*char_ptr;
	int		player_and_exit_check;

	map_grid_ptr = data->map->map_grid;
	player_and_exit_check = 0;
	data->map->coll_cnt = 0;
	while (*map_grid_ptr != NULL)
	{
		char_ptr = *map_grid_ptr;
		while (*char_ptr != '\0')
		{
			if (*char_ptr == 'C')
				data->map->coll_cnt++;
			else if (*char_ptr == 'P' || *char_ptr == 'E')
				player_and_exit_check++;
			else if (*char_ptr != '1' && *char_ptr != '0')
				msg_err_and_exit(data, ERR_UNDEF_ITEM);
			char_ptr++;
		}
		map_grid_ptr++;
	}
	if (data->map->coll_cnt == 0 || player_and_exit_check != 2)
		return (FAIL);
	return (SUCCESS);
}

// Saves initial player and exit posiotions.
// param:
// - 'data' - game data structure.
//
static void	save_initial_player_and_exit_positions(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map->map_grid[y] != NULL)
	{
		x = 0;
		while (data->map->map_grid[y][x])
		{
			if (data->map->map_grid[y][x] == 'P')
			{
				data->map->player_pos.y = y;
				data->map->player_pos.x = x;
			}
			else if (data->map->map_grid[y][x] == 'E')
			{
				data->map->exit_pos.y = y;
				data->map->exit_pos.x = x;
			}
			x++;
		}
		y++;
	}
	data->map->player_moves_cnt = 0;
	data->map->game_finished = 0;
}

// Main function to validate all the necessary map elements.
// Using helper function for checking.
// Sets initial game state.
// param:
// - 'data' - game data (including the map).
//
void	process_and_validate_map(t_data *data)
{
	char	**map_grid_ptr;

	data->map->width = ft_strlen(data->map->map_grid[0]);
	map_grid_ptr = data->map->map_grid;
	data->map->height = 0;
	while (*map_grid_ptr++ != NULL)
		data->map->height++;
	if (check_if_map_is_rectangle(data) == FAIL)
		msg_err_and_exit(data, ERR_NO_RECT);
	if (check_if_map_is_closed(data))
		msg_err_and_exit(data, ERR_NOT_CLOSED);
	if (check_objects(data) == FAIL)
		msg_err_and_exit(data, ERR_NO_ITEMS);
	if (check_if_all_objects_are_reachable(data) == FAIL)
		msg_err_and_exit(data, ERR_NO_PATH);
	save_initial_player_and_exit_positions(data);
}
