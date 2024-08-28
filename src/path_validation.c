/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:53:57 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/08/27 20:58:33 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Init point data for validate a path.
// Allocates memory for tracking visited points 
// and sets initial directions for movement.
// param:
// - 'data' - game data structure.
// - 'point_data' - struct to hold validated data.
//
static void	populate_point_data(t_data *data, t_point_data *point_data)
{
	point_data->visited_points = (t_point *)malloc(sizeof(t_point)
			* data->map->height * data->map->width);
	if (!point_data->visited_points)
		msg_err_and_exit(data, ERR_MALLOC);
	point_data->new_point_dir[0].x = -1;
	point_data->new_point_dir[0].y = 0;
	point_data->new_point_dir[1].x = 0;
	point_data->new_point_dir[1].y = -1;
	point_data->new_point_dir[2].x = 1;
	point_data->new_point_dir[2].y = 0;
	point_data->new_point_dir[3].x = 0;
	point_data->new_point_dir[3].y = 1;
}

// Check if current point was already visited in validation process.
// Compare current point with visited points list.
// params:
// - 'point_data' - struct to hold validated data.
// - 'now_point' - current point to check.
//
static int	point_already_visited(t_point_data *point_data, t_point now_point)
{
	size_t	i;

	i = 0;
	while (i < point_data->v_point_size)
	{
		if (now_point.x == point_data->visited_points[i].x
			&& now_point.y == point_data->visited_points[i].y)
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
// - 'point_data' - struct to hold validated data.
// - 'now_point' - current point to check.
//
static void	check_path_to_exit(char **map_grid_ptr,
				t_point_data *point_data, t_point now_point)
{
	t_point	temp_point;
	int		i;

	i = 0;
	while (i < 4)
	{
		temp_point.x = now_point.x + point_data->new_point_dir[i].x;
		temp_point.y = now_point.y + point_data->new_point_dir[i].y;
		if (map_grid_ptr[temp_point.y][temp_point.x] != '1'
			&& !point_already_visited(point_data, temp_point)
			&& !point_data->path_exists_flg == SUCCESS)
		{
			if (map_grid_ptr[temp_point.y][temp_point.x] == 'E')
				point_data->path_exists_flg = SUCCESS;
			else
			{
				point_data->v_point_size++;
				point_data->visited_points[point_data->v_point_size - 1].x = temp_point.x;
				point_data->visited_points[point_data->v_point_size - 1].y = temp_point.y;
				check_path_to_exit(map_grid_ptr, point_data, temp_point);
			}
		}
		i++;
	}
}

static void	check_path_from_coll(char **map_grid_ptr,
				t_point_data *point_data, t_point now_point)
{
	t_point	temp_point;
	int		i;

	i = 0;
	while (i < 4)
	{
		temp_point.x = now_point.x + point_data->new_point_dir[i].x;
		temp_point.y = now_point.y + point_data->new_point_dir[i].y;
		if (map_grid_ptr[temp_point.y][temp_point.x] != '1'
			&& map_grid_ptr[temp_point.y][temp_point.x] != 'E'
			&& !point_already_visited(point_data, temp_point)
			&& !point_data->path_exists_flg == SUCCESS)
		{
			if (map_grid_ptr[temp_point.y][temp_point.x] == 'P')
				point_data->path_exists_flg = SUCCESS;
			else
			{
				point_data->v_point_size++;
				point_data->visited_points[point_data->v_point_size - 1].x = temp_point.x;
				point_data->visited_points[point_data->v_point_size - 1].y = temp_point.y;
				check_path_from_coll(map_grid_ptr, point_data, temp_point);
			}
		}
		i++;
	}
}

// Check if this specific object is reachable.
// Looking for a path from object, to Exit.
// params:
// - 'map_grid_ptr' - pointer to map grid.
// - 'point_data' - struct to hold validated data.
// - 'x' & 'y' - object coordinates.
//
static int	check_this_obj_being_reachable(char **map_grid_ptr,
				t_point_data *point_data, int x, int y)
{
	t_point	start_point;

	point_data->v_point_size = 0;
	start_point.x = x;
	start_point.y = y;
	point_data->path_exists_flg = FAIL;
	check_path_to_exit(map_grid_ptr, point_data, start_point);
	if (point_data->path_exists_flg == FAIL)
	{
		free(point_data->visited_points);
		return (FAIL);
	}
	return (SUCCESS);
}

static int	check_coll_being_reachable(char **map_grid_ptr,
				t_point_data *point_data, int x, int y)
{
	t_point	start_point;

	point_data->v_point_size = 0;
	start_point.x = x;
	start_point.y = y;
	point_data->path_exists_flg = FAIL;
	check_path_from_coll(map_grid_ptr, point_data, start_point);
	if (point_data->path_exists_flg == FAIL)
	{
		free(point_data->visited_points);
		return (FAIL);
	}
	return (SUCCESS);
}

// Checks if all objects ('P' - player, 'C' - collectable) are reachable.
// Iterater through the map to find a path between object and Exit ('E').
// Returns FAIL if path doesn't exist.
// param:
// - 'data' - game data structure.
//
int	check_if_all_objects_are_reachable(t_data *data)
{
	char			**map_grid_ptr;
	t_point_data	point_data;
	int				i;
	int				j;

	populate_point_data(data, &point_data);
	map_grid_ptr = data->map->map_grid;
	i = 0;
	while (map_grid_ptr[i] != NULL)
	{
		j = 0;
		while (map_grid_ptr[i][j] != '\0')
		{
			if (map_grid_ptr[i][j] == 'P')
			{
				if (check_this_obj_being_reachable(map_grid_ptr,
						&point_data, j, i) == FAIL)
					return (FAIL);
			}
			else if (map_grid_ptr[i][j] == 'C')
			{
				if (check_coll_being_reachable(map_grid_ptr,
						&point_data, j, i) == FAIL)
					return (FAIL);
			}
			j++;
		}
		i++;
	}
	free(point_data.visited_points);
	return (SUCCESS);
}
