/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:42:44 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/08/28 22:17:44 by pjedrycz         ###   ########.fr       */
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

//ft_itoa helper function - 
//returns number of digits in the intiger.
//
static int	ft_intlen(long nbr)
{
	int	count;

	count = 0;
	if (nbr < 0)
	{
		count++;
		nbr = -nbr;
	}
	if (nbr == 0)
	{
		count++;
	}
	while (nbr != 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

//ft_itoa helper function -
//allocates memory for converted string.
//
static char	*ft_preconv(int len)
{
	char	*tmp;

	tmp = malloc((len + 1) * sizeof(char));
	if (!tmp)
	{
		return (NULL);
	}
	tmp[0] = '0';
	return (tmp);
}

// Converts integer to a string.
// param:
// - 'n' - integer to convert.
//
char	*ft_itoa(int n)
{
	int		len;
	int		i;
	char	*result;
	long	nbr;

	nbr = n;
	len = ft_intlen(nbr);
	result = ft_preconv(len);
	if (!result)
		return (NULL);
	if (nbr < 0)
		nbr = -nbr;
	i = len - 1;
	while (nbr != 0)
	{
		result[i] = ((nbr % 10) + 48);
		nbr = nbr / 10;
		i--;
	}
	if (n < 0)
		result[0] = '-';
	result[len] = 0;
	return (result);
}

// Calculates string length.
// param:
// - 's' - string to calculate.
//
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
