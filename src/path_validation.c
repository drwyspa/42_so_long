/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:53:57 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/09/03 22:46:12 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Init point data for validate a path.
// Allocates memory for tracking visited points 
// and sets initial directions for movement.
// param:
// - 'data' - game data structure.
// - 'pnt_data' - struct to hold validated data.
//
static void	populate_pnt_data(t_data *data, t_point_data *pnt_data)
{
	pnt_data->visited_pnts = (t_point *)malloc(sizeof(t_point)
			* data->map->height * data->map->width);
	if (!pnt_data->visited_pnts)
		msg_err_and_exit(data, ERR_MALLOC);
	pnt_data->new_pnt_dir[0].x = -1;
	pnt_data->new_pnt_dir[0].y = 0;
	pnt_data->new_pnt_dir[1].x = 0;
	pnt_data->new_pnt_dir[1].y = -1;
	pnt_data->new_pnt_dir[2].x = 1;
	pnt_data->new_pnt_dir[2].y = 0;
	pnt_data->new_pnt_dir[3].x = 0;
	pnt_data->new_pnt_dir[3].y = 1;
}

// Check if this specific object is reachable.
// Looking for a path from object, to Exit.
// params:
// - 'map_grid_ptr' - pointer to map grid.
// - 'pnt_data' - struct to hold validated data.
// - 'x' & 'y' - object coordinates.
//
static int	check_obj_reachable(char **map_grid_ptr,
				t_point_data *pnt_data, int x, int y)
{
	t_point	start_pnt;

	pnt_data->v_pnt_size = 0;
	start_pnt.x = x;
	start_pnt.y = y;
	pnt_data->path_exists_flg = FAIL;
	check_path_to_exit(map_grid_ptr, pnt_data, start_pnt);
	if (pnt_data->path_exists_flg == FAIL)
	{
		free(pnt_data->visited_pnts);
		return (FAIL);
	}
	return (SUCCESS);
}

static int	check_coll_reachable(char **map_grid_ptr,
				t_point_data *pnt_data, int x, int y)
{
	t_point	start_pnt;

	pnt_data->v_pnt_size = 0;
	start_pnt.x = x;
	start_pnt.y = y;
	pnt_data->path_exists_flg = FAIL;
	check_path_from_coll(map_grid_ptr, pnt_data, start_pnt);
	if (pnt_data->path_exists_flg == FAIL)
	{
		free(pnt_data->visited_pnts);
		return (FAIL);
	}
	return (SUCCESS);
}

// Checks if all objects ('P' - player, 'C' - collectable) are reachable.
// Iterate through the map to find a path between object and Exit ('E').
// Returns FAIL if path doesn't exist.
// param:
// - 'data' - game data structure.
//
int	check_if_all_objects_are_reachable(t_data *data)
{
	char			**map_grid_ptr;
	t_point_data	pnt_data;
	int				i;
	int				j;

	populate_pnt_data(data, &pnt_data);
	map_grid_ptr = data->map->map_grid;
	i = 0;
	while (map_grid_ptr[i] != NULL)
	{
		j = 0;
		while (map_grid_ptr[i][j] != '\0')
		{
			if (map_grid_ptr[i][j] == 'P' &&
				check_obj_reachable(map_grid_ptr, &pnt_data, j, i) == FAIL)
				return (FAIL);
			else if (map_grid_ptr[i][j] == 'C' &&
				check_coll_reachable(map_grid_ptr, &pnt_data, j, i) == FAIL)
				return (FAIL);
			j++;
		}
		i++;
	}
	free(pnt_data.visited_pnts);
	return (SUCCESS);
}
