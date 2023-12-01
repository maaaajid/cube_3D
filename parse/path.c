/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 00:31:51 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/11/28 08:34:03 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	get_path(char *line)
{
	int		fd;
	char	**splited;

	fd = 0;
	splited = ft_split(line, ' ');
	fd = open(splited[1], O_RDONLY | __O_DIRECTORY);
	if (fd > 0)
	{
		ft_free(splited);
		close(fd);
		print_error("It's a directory\n");
	}
	fd = open(splited[1], O_RDONLY);
	if (fd < 0)
	{
		ft_free(splited);
		print_error("Wrong Texture File\n");
	}
	if (ft_strncmp(splited[1] + (ft_strlen(splited[1]) - 4), ".xpm", 4))
	{
		ft_free(splited);
		print_error("Wrong Texture File\n");
	}
	ft_free(splited);
}

void	fill_textures(t_map *map, char *line)
{
	char	**splited;

	splited = ft_split(line, ' ');
	if (ft_strncmp("NO", splited[0], 3) == 0)
		map->no = ft_strdup(splited[1]);
	else if (ft_strncmp("SO", splited[0], 3) == 0)
		map->so = ft_strdup(splited[1]);
	else if (ft_strncmp("EA", splited[0], 3) == 0)
		map->ea = ft_strdup(splited[1]);
	else if (ft_strncmp("WE", splited[0], 3) == 0)
		map->we = ft_strdup(splited[1]);
	ft_free(splited);
}

void	fill_rgb(t_map *map, char *line)
{
	char	**splited;
	char	**color;

	splited = ft_split(line, ' ');
	color = ft_split(splited[1], ',');
	if (color[0] && color[1] && color[2])
	{
		if (ft_strncmp("F", splited[0], 2) == 0)
		{
			map->f_r = ft_atoi(color[0]);
			map->f_g = ft_atoi(color[1]);
			map->f_b = ft_atoi(color[2]);
		}
		else if (ft_strncmp("C", splited[0], 2) == 0)
		{
			map->c_r = ft_atoi(color[0]);
			map->c_g = ft_atoi(color[1]);
			map->c_b = ft_atoi(color[2]);
		}
	}
	else
		print_error("Invalid Format\n");
	ft_free(splited);
	ft_free(color);
}

void	mini_window(void)
{
	if (WINDOW_WIDTH > 1700.0 || WINDOW_WIDTH < 100.0)
		print_error("Incompatible window\n");
	else if (WINDOW_HIEGHT > 1200.0 || WINDOW_HIEGHT < 100.0)
		print_error("Incompatible window\n");
	else if (RAYS < 300.0 || RAYS > 3600.0)
		print_error("Incompatible window\n");
	else if (FOV < 60.0 || FOV > 90.0)
		print_error("Incompatible window\n");
}
