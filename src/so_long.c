/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:23:51 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/08/28 22:18:51 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Reads the map file and loads to game data structure.

// Opens a file from a file_path parameter
// and read it into a buffer.
// Using ft_split - data is divided into a grid using '\n',
// to creates game map.

// params:
// - 'data' - pointer to the game data structure, to store
// loaded map.
// - 'file_path' - path to map file.
//
static void	load_map(t_data *data, char *file_path)
{
	int		fd;
	char	*loaded_map_ptr;
	ssize_t	bytes_read;

	fd = open(file_path, O_RDWR);
	if (fd == -1)
		msg_err_and_exit(data, ERR_FILE);
	loaded_map_ptr = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!loaded_map_ptr)
		msg_err_and_exit(data, ERR_MALLOC);
	bytes_read = read(fd, loaded_map_ptr, BUFFER_SIZE);
	if (bytes_read == -1)
		msg_err_and_exit(data, ERR_FILE);
	loaded_map_ptr[bytes_read] = '\0';
	data->map->map_grid = ft_split(loaded_map_ptr, '\n');
	if (!data->map->map_grid)
	{
		free(loaded_map_ptr);
		msg_err_and_exit(data, ERR_MALLOC);
	}
	close(fd);
	free(loaded_map_ptr);
}

// Exits the game and cleans all game data.
// param:
// - 'data' pointer to the game data struct.
//
int	on_destroy(t_data *data)
{
	free_textures(data);
	free_map_grid(data);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(SUCCESS);
	return (SUCCESS);
}

// Init game data, loads the map, create game window,
// starts main game loop (for events).
// Error handlings included.
// params:
// - 'argc' - number of arguments from the user input.
// - 'argv' - game file name & map files + path to it.
//
int	main(int argc, char **argv)
{
	t_data	data;
	t_map	map;

	data.mlx_ptr = NULL;
	data.win_ptr = NULL;
	map.map_grid = NULL;
	data.map = &map;
	if (argc != 2)
		msg_err_and_exit(&data, ERR_NO_FILE_PATH);
	load_map(&data, argv[1]);
	process_and_validate_map(&data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		msg_err_and_exit(&data, ERR_MLX);
	data.win_ptr = mlx_new_window(data.mlx_ptr, map.width * TILE_SIZE,
			map.height * TILE_SIZE, GAME_TITLE);
	if (!data.win_ptr)
		msg_err_and_exit(&data, ERR_MLX_WIN);
	load_textures(&data);
	draw_static_elements(&data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask,
		&on_destroy, &data);
	mlx_loop(data.mlx_ptr);
}
