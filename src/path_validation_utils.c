/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:53:57 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/09/03 21:36:08 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Check if current point was already visited in validation process.
// Compare current point with visited points list.
// params:
// - 'pnt_data' - struct to hold validated data.
// - 'now_pnt' - current point to check.
//
int	pnt_already_visited(t_point_data *pnt_data, t_point now_pnt)
{
	size_t	i;

	i = 0;
	while (i < pnt_data->v_pnt_size)
	{
		if (now_pnt.x == pnt_data->visited_pnts[i].x
			&& now_pnt.y == pnt_data->visited_pnts[i].y)
			return (1);
		i++;
	}
	return (0);
}

// Recursive function for checking a path to exit,
// from current point.
// Check all sorrounding points (excluding walls) which werent visited yet.
// Marks the 'E' as found if reached.
//params:
// - 'map_grid_ptr' - pointer to the map grid.
// - 'pnt_data' - struct to hold validated data.
// - 'now_pnt' - current point to check.
//
void	check_path_to_exit(char **map_grid_ptr,
				t_point_data *pnt_data, t_point now_pnt)
{
	t_point	temp_pnt;
	int		i;

	i = 0;
	while (i < 4)
	{
		temp_pnt.x = now_pnt.x + pnt_data->new_pnt_dir[i].x;
		temp_pnt.y = now_pnt.y + pnt_data->new_pnt_dir[i].y;
		if (map_grid_ptr[temp_pnt.y][temp_pnt.x] != '1'
			&& !pnt_already_visited(pnt_data, temp_pnt)
			&& !pnt_data->path_exists_flg == SUCCESS)
		{
			if (map_grid_ptr[temp_pnt.y][temp_pnt.x] == 'E')
				pnt_data->path_exists_flg = SUCCESS;
			else
			{
				pnt_data->v_pnt_size++;
				pnt_data->visited_pnts[pnt_data->v_pnt_size - 1].x = temp_pnt.x;
				pnt_data->visited_pnts[pnt_data->v_pnt_size - 1].y = temp_pnt.y;
				check_path_to_exit(map_grid_ptr, pnt_data, temp_pnt);
			}
		}
		i++;
	}
}

// Recursive function for checking a path from collectible to player,
// Check all sorrounding points (excluding walls and exit) 
//which werent visited yet.
//params:
// - 'map_grid_ptr' - pointer to the map grid.
// - 'pnt_data' - struct to hold validated data.
// - 'now_pnt' - current point to check.
//
void	check_path_from_coll(char **map_grid_ptr,
				t_point_data *pnt_data, t_point now_pnt)
{
	t_point	temp_pnt;
	int		i;

	i = 0;
	while (i < 4)
	{
		temp_pnt.x = now_pnt.x + pnt_data->new_pnt_dir[i].x;
		temp_pnt.y = now_pnt.y + pnt_data->new_pnt_dir[i].y;
		if (map_grid_ptr[temp_pnt.y][temp_pnt.x] != '1'
			&& map_grid_ptr[temp_pnt.y][temp_pnt.x] != 'E'
			&& !pnt_already_visited(pnt_data, temp_pnt)
			&& !pnt_data->path_exists_flg == SUCCESS)
		{
			if (map_grid_ptr[temp_pnt.y][temp_pnt.x] == 'P')
				pnt_data->path_exists_flg = SUCCESS;
			else
			{
				pnt_data->v_pnt_size++;
				pnt_data->visited_pnts[pnt_data->v_pnt_size - 1].x = temp_pnt.x;
				pnt_data->visited_pnts[pnt_data->v_pnt_size - 1].y = temp_pnt.y;
				check_path_from_coll(map_grid_ptr, pnt_data, temp_pnt);
			}
		}
		i++;
	}
}
