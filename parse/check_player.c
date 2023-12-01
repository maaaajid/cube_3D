/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 02:24:08 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/11/28 04:07:35 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

int	find_start_position(t_map *map, t_rayc *rayc)
{
	int		i;
	int		j;
	char	current;

	i = -1;
	while (map->split_map[++i])
	{
		j = -1;
		while (map->split_map[i][++j])
		{
			current = map->split_map[i][j];
			if (current == 'N' || current == 'S' || current == 'E'
				|| current == 'W')
			{
				map->player_found++;
				rayc->pp_x = (j * 50) + 25;
				rayc->pp_y = (i * 50) + 25;
				map->caracter = current;
				map->split_map[i][j] = '0';
			}
		}
	}
	if (map->player_found > 1)
		print_error("More than 1 player in the map\n");
	return (0);
}

int	set_player_vision(t_map *map)
{
	if (map->caracter == 'N')
		return (270);
	else if (map->caracter == 'S')
		return (90);
	else if (map->caracter == 'W')
		return (0);
	else
		return (180);
}

void	check_args(char **av, t_map *map)
{
	if (map_name(map->name))
		print_error("Invalid file name\n");
	map->fd = open(av[1], O_RDONLY | __O_DIRECTORY);
	if (map->fd > 0)
	{
		print_error("It's a directory\n");
		close(map->fd);
	}
	map->fd = open(av[1], O_RDONLY);
	if (map->fd < 0)
		print_error("File does not exist\n");
	map->argv = av[1];
}

int	check_verg(char *str)
{
	int	i;
	int	verg;

	i = 0;
	verg = 0;
	while (str[i])
	{
		if (str[i] == ',' && str[i + 1] == ',')
			print_error("Invalid Format\n");
		if (str[i] == ',')
			verg++;
		i++;
		if (verg > 2)
			print_error("Invalid Format\n");
	}
	return (verg);
}

void	check_last_line(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i + 1])
		i++;
	while (map[i][j])
	{
		if (map[i][j] != ' ' && map[i][j] != '1')
			print_error("Invalid Map\n");
		j++;
	}
}
