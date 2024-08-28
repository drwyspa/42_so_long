/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 22:26:19 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/08/20 20:46:08 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_initiate_vars(size_t *i, int *j, int *s_word)
{
	*i = 0;
	*j = 0;
	*s_word = -1;
}

static int	ft_words(const char *str, char c)
{
	int	number;
	int	flag;

	number = 0;
	flag = 0;
	while (*str)
	{
		if (*str != c && flag == 0)
		{
			flag = 1;
			number++;
		}
		else if (*str == c)
			flag = 0;
		str++;
	}
	return (number);
}

static char	*ft_wordcpy(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start +1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static void	*ft_free(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

// Using this function to split string (from map file)
// to an array. We're taking '\n' as a end of each row.
// This way we can create map grid.
// params:
// - 's' - input string.
// - 'c' - delimiter.
//
char	**ft_split(const char *s, char c)
{
	char	**res;
	size_t	i;
	int		j;
	int		s_word;

	ft_initiate_vars(&i, &j, &s_word);
	res = ft_calloc((ft_words(s, c) + 1), sizeof(char *));
	if (!res)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && s_word < 0)
			s_word = i;
		else if ((s[i] == c || i == ft_strlen(s)) && s_word >= 0)
		{
			res[j] = ft_wordcpy(s, s_word, i);
			if (!(res[j]))
				return (ft_free(res, j));
			s_word = -1;
			j++;
		}
		i++;
	}
	return (res);
}
