/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 05:42:40 by aelbouaa          #+#    #+#             */
/*   Updated: 2023/11/30 22:36:39 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/Cub3D.h"

void	sliding(t_rayc *rayc, double old_x_cos, double old_y_sin)
{
	if (rayc->map[(int)(rayc->pp_y + ((int)rayc->y_sin[RAYS / 2])) / 50]
	[(int)rayc->pp_x / 50] != '1'
		&& rayc->x_cos[RAYS / 2] < 3 && rayc->x_cos[RAYS / 2] > -3)
	{
		rayc->pp_y += ((int)rayc->y_sin[RAYS / 2] / 2);
		rayc->pp_x -= (int)rayc->x_cos[RAYS / 2];
		draw_rays(rayc);
	}
	else if (rayc->map[(int)rayc->pp_y / 50]
		[(int)(rayc->pp_x + ((int)rayc->x_cos[RAYS / 2])) / 50] != '1'
		&& rayc->y_sin[RAYS / 2] < 3 && rayc->y_sin[RAYS / 2] > -3)
	{
		rayc->pp_x += ((int)rayc->x_cos[RAYS / 2] / 2);
		rayc->pp_y -= (int)rayc->y_sin[RAYS / 2];
		draw_rays(rayc);
	}
	else
	{
		rayc->pp_x -= (int)rayc->x_cos[RAYS / 2];
		rayc->pp_y -= (int)rayc->y_sin[RAYS / 2];
		rayc->x_cos[RAYS / 2] = old_x_cos;
		rayc->y_sin[RAYS / 2] = old_y_sin;
	}
}

void	game(t_rayc *rayc, t_map *map)
{
	int		x;
	int		dir;
	double	inc;

	x = 0;
	dir = set_player_vision(map);
	rayc->ptr = mlx_init();
	read_textures(rayc, map);
	rayc->window = mlx_new_window(rayc->ptr, WINDOW_WIDTH,
			WINDOW_HIEGHT, "cub3d");
	inc = (double)FOV / (double)RAYS;
	while (x < RAYS)
	{
		rayc->angel[x] = (dir - (FOV / 2)) + inc;
		rayc->ray[x] = 0;
		inc += (double)FOV / (double)RAYS;
		x++;
	}
	draw_rays(rayc);
	mlx_hook(rayc->window, 3, 3, &player, rayc);
	mlx_hook(rayc->window, 17, 0, &ft_close, NULL);
	mlx_loop(rayc->ptr);
}

int	main(int ac, char **av)
{
	int		x;
	t_rayc	*rayc;
	t_map	*map;

	x = -1;
	rayc = malloc(sizeof(t_rayc));
	map = malloc(sizeof(t_map));
	ft_memset(map, 0, sizeof(t_map));
	if (ac == 2)
	{
		map->name = av[1];
		final_check(ac, av, map, rayc);
		rayc->map = map->split_map;
		rayc->floor_rgb = get_rgb(map->f_r, map->f_g, map->f_b);
		rayc->ceiling_rgb = get_rgb(map->c_r, map->c_g, map->c_b);
		while (++x < 5)
			rayc->data[x] = malloc(sizeof(t_data));
		game(rayc, map);
	}
	else
		printf("INVALID ARGS\n");
	free(map);
	return (0);
}
