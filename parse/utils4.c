/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:34:48 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/11/23 17:06:37 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

int	biggest_line(char **map)
{
	int	i;
	int	line;

	i = 0;
	line = 0;
	while (map[i])
	{
		if (line < (int)ft_strlen(map[i]))
			line = (int)ft_strlen(map[i]);
		i++;
	}
	return (line);
}

int	count_line_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	check_is_open(int i, int j, char **dup)
{
	if (dup[j][i] != 'X' && dup[j][i] != '1')
		return (1);
	return (0);
}

int	is_inside_map(int x, int y, int width, int height)
{
	return (x >= 0 && x < width && y >= 0 && y < height);
}

int	is_valid(char *map)
{
	char	current;
	int		i;

	i = 0;
	while (map[i])
	{
		current = map[i];
		if (current != '0' && current != '1' && current != 'N' && current != 'S'
			&& current != 'E' && current != 'W' && current != ' ')
			return (1);
		i++;
	}
	return (0);
}
