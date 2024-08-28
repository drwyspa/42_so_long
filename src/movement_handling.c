/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 21:35:43 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/08/28 22:20:31 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Based on pressed keym, calculates desired position for player.
// params:
// - 'current_pos' - Current, player position.
// - 'keysym' - pressed key, key symbol.
//
static t_point	calc_next_player_position(t_point current_pos, int keysym)
{
	if (keysym == 65363)
		current_pos.x++;
	else if (keysym == 65361)
		current_pos.x--;
	else if (keysym == 65362)
		current_pos.y--;
	else if (keysym == 65364)
		current_pos.y++;
	return (current_pos);
}

// Check validation of the next move - based on game map construction.
// Updates game state, like collectables number and exit state.
// params:
// - 'data' game data with player position and the map.
// - 'next_pos' - desired next position of the player.
//
static int	check_next_move(t_data *data, t_point next_pos)
{
	t_map	*map;

	map = data->map;
	if (map->map_grid[next_pos.y][next_pos.x] == '1')
		return (FAIL);
	if (map->map_grid[next_pos.y][next_pos.x] == 'E'
			&& map->coll_cnt != 0)
		return (FAIL);
	else if (map->map_grid[next_pos.y][next_pos.x] == 'C')
	{
		map->coll_cnt--;
		map->map_grid[next_pos.y][next_pos.x] == '0';
		if (map->coll_cnt == 0)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->textures[5], data->map->exit_pos.x * TILE_SIZE,
				data->map->exit_pos.y * TILE_SIZE);
	}
	else if (map->map_grid[next_pos.y][next_pos.x] == 'E'
		&& map->coll_cnt == 0)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->textures[6], ((data->map->width / 2 - 1) * TILE_SIZE), 0);
		data->map->game_finished = 1;
	}
	return (SUCCESS);
}

// Updates and draw on the map, player new position.
// params:
// - 'data'- game data with player position and the map.
// - 'keysym' - pressed key symbol. 
//
static void	update_and_draw_player_new_position(t_data *data, int keysym)
{
	t_map	*map;

	map = data->map;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->textures[0], map->player_pos.x * TILE_SIZE,
		map->player_pos.y * TILE_SIZE);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->textures[3], map->player_pos.x * TILE_SIZE,
		map->player_pos.y * TILE_SIZE);
}

static void	display_player_moves_cnt(t_data *data)
{
	char	*message;
	char	*nbr;

	message = "Player moves count: ";
	nbr = ft_itoa(data->map->player_moves_cnt);
	if (!nbr)
		msg_err_and_exit(data, ERR_MALLOC);
	write(1, message, ft_strlen(message));
	write(1, nbr, ft_strlen(nbr));
	write(1, "\n", 1);
	free(nbr);
}

// Keyboard command handling. 
// Calculates player movement based on key press.
// ESC = exit the game.
// Params:
// - 'keysym' - key symbol of used key.
// - 'data' - game data with the map and player position.
//
int	on_keypress(int keysym, t_data *data)
{
	t_point	next_pos;
	t_point	current_pos;

	if (keysym == 65307)
		on_destroy(data);
	if (keysym != 65361 && keysym != 65362
		&& keysym != 65363 && keysym != 65364)
		return (FAIL);
	if (data->map->game_finished == 1)
		return (FAIL);
	current_pos = data->map->player_pos;
	next_pos = calc_next_player_position(current_pos, keysym);
	if (check_next_move(data, next_pos) == SUCCESS)
	{
		update_and_draw_player_new_position(data, keysym);
		data->map->player_moves_cnt++;
		display_player_moves_cnt(data);
	}
	return (SUCCESS);
}
