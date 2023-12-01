/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheking_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:24:42 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/11/26 15:24:30 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

char	*fill_map(int width, char *line)
{
	char	*fill_line;
	int		i;
	int		j;

	fill_line = ft_calloc((width + 3), sizeof(char));
	i = 0;
	if (line)
		fill_line[i++] = 'X';
	j = 0;
	while (i < width + 2)
	{
		if (line && j < (int)ft_strlen(line) && ft_strchr("10NSWE", line[j]))
			fill_line[i] = line[j];
		else
			fill_line[i] = 'X';
		i++;
		j++;
	}
	fill_line[i] = '\0';
	return (fill_line);
}

char	**dup_map(t_map *map, int width, int height)
{
	int		i;
	char	**dup;
	int		j;

	dup = ft_calloc(height + 3, sizeof(char *));
	dup[0] = fill_map(width, NULL);
	i = 1;
	j = 0;
	while (i < height + 1)
	{
		dup[i] = fill_map(width, map->split_map[j]);
		i++;
		j++;
	}
	dup[i] = fill_map(width, NULL);
	dup[i + 1] = NULL;
	return (dup);
}

int	check_closed_map(char **dup_map, int y, int width, int height)
{
	int	x;

	while (dup_map[y])
	{
		x = 0;
		while (dup_map[y][x])
		{
			if (dup_map[y][x] == 'X')
			{
				if ((dup_map[y][x + 1] && check_is_open(x + 1, y, dup_map))
					|| (dup_map[y + 1] && check_is_open(x, y + 1, dup_map)))
					return (ft_free(dup_map), 1);
				else if ((is_inside_map(x - 1, y, width, height)
						&& check_is_open(x - 1, y, dup_map))
					|| (is_inside_map(x, y - 1, width, height)
						&& check_is_open(x, y - 1, dup_map)))
					return (ft_free(dup_map), 1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	check_walls(t_map *map)
{
	char	**dup;
	int		y;
	int		height;
	int		width;

	height = count_line_map(map->split_map);
	width = biggest_line(map->split_map);
	dup = NULL;
	dup = dup_map(map, width, height);
	y = 0;
	if (!dup || check_closed_map(dup, y, width, height))
		return (1);
	ft_free(dup);
	return (0);
}

void	final_map_check(t_map *map, t_rayc *rayc)
{
	int	i;

	i = 0;
	while (map->split_map[i])
	{
		if (is_valid(map->split_map[i]))
			print_error("Invalid Caracter in the map\n");
		i++;
	}
	find_start_position(map, rayc);
	if (check_walls(map) || map->player_found == 0)
		print_error("Invalid Map\n");
}
