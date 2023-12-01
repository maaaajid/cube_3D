/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:24:25 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/11/28 03:28:47 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	check_lenght(char **str)
{
	int	i;
	int	j;
	int	check;

	i = -1;
	check = 0;
	if (ft_strchr(str[0], 'C'))
		str[0] = ft_strtrim(str[0], "C ");
	else
		str[0] = ft_strtrim(str[0], "F ");
	str[1] = ft_strtrim(str[1], " ");
	str[2] = ft_strtrim(str[2], " ");
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (!ft_isdigit(str[i][j]))
				print_error("only digits\n");
		}
		if (ft_strlen(str[i]) > 3)
			check += 1;
	}
	if (i != 3 || check)
		print_error("Invalid color format\n");
}

void	check_digits(char *str)
{
	int		i;
	char	**color;
	char	*coloradd1;
	char	*coloradd2;
	char	*coloradd3;

	i = -1;
	if (!ft_strchr(str, ','))
		print_error("Invalid Format\n");
	if (check_verg(str) < 2)
		print_error("Invalid Format\n");
	color = ft_split(str, ',');
	coloradd1 = color[0];
	coloradd3 = color[1];
	coloradd2 = color[2];
	check_lenght(color);
	while (color[++i])
	{
		if (!((ft_atoi(color[i]) >= 0) && (ft_atoi(color[i]) <= 255)))
			print_error("invalid range [0,255]\n");
	}
	ft_free(color);
	free(coloradd1);
	free(coloradd3);
	free(coloradd2);
}

void	check_textures_id(char *str, t_vars *id)
{
	if (ft_strncmp(str, "NO ", 3) == 0)
		id->no++;
	else if (ft_strncmp(str, "SO ", 3) == 0)
		id->so++;
	else if (ft_strncmp(str, "EA ", 3) == 0)
		id->ea++;
	else if (ft_strncmp(str, "WE ", 3) == 0)
		id->we++;
	else if (ft_strncmp(str, "F ", 2) == 0)
		id->f++;
	else if (ft_strncmp(str, "C ", 2) == 0)
		id->c++;
	if (id->no > 1 || id->c > 1 || id->ea > 1 || id->so > 1 || id->f > 1
		|| id->we > 1)
		print_error("Duplicated id\n");
}

void	check_textures_helper(char *str, t_vars *vars, t_map *map)
{
	if (ft_strncmp(str, "NO ", 3) == 0 || ft_strncmp(str, "SO ", 3) == 0
		|| ft_strncmp(str, "WE ", 3) == 0 || ft_strncmp(str, "EA ", 3) == 0)
	{
		check_textures_id(str, vars);
		get_path(str);
		map->count++;
	}
	else if (ft_strncmp(str, "F ", 2) == 0 || ft_strncmp(str, "C ", 2) == 0)
	{
		check_textures_id(str, vars);
		check_digits(str);
		fill_rgb(map, str);
		map->count++;
	}
	else
		print_error("Wrong textures id\n");
}

void	check_textures(t_map *map)
{
	int		i;
	char	*str;
	t_vars	vars;

	i = -1;
	str = NULL;
	ft_memset(&vars, 0, sizeof(t_vars));
	while (map->split_text[++i] && map->count != 6)
	{
		str = map->split_text[i];
		while (my_isspace(*str))
			str++;
		check_textures_helper(str, &vars, map);
		fill_textures(map, str);
	}
}
