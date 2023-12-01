/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 06:11:39 by aelbouaa          #+#    #+#             */
/*   Updated: 2023/11/30 02:38:30 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/Cub3D.h"

void	get_data_addr(t_rayc *rayc)
{
	rayc->data[1]->addr = mlx_get_data_addr(rayc->data[1]->img,
			&rayc->data[1]->bits_per_pixel, &rayc->data[1]->line_length,
			&rayc->data[1]->endian);
	rayc->data[2]->addr = mlx_get_data_addr(rayc->data[2]->img,
			&rayc->data[2]->bits_per_pixel, &rayc->data[2]->line_length,
			&rayc->data[2]->endian);
	rayc->data[3]->addr = mlx_get_data_addr(rayc->data[3]->img,
			&rayc->data[3]->bits_per_pixel, &rayc->data[3]->line_length,
			&rayc->data[3]->endian);
	rayc->data[4]->addr = mlx_get_data_addr(rayc->data[4]->img,
			&rayc->data[4]->bits_per_pixel, &rayc->data[4]->line_length,
			&rayc->data[4]->endian);
}

void	read_textures(t_rayc *rayc, t_map *map)
{
	rayc->data[1]->img = mlx_xpm_file_to_image(rayc->ptr,
			map->no, &rayc->data[1]->w, &rayc->data[1]->h);
	rayc->data[2]->img = mlx_xpm_file_to_image(rayc->ptr,
			map->so, &rayc->data[2]->w, &rayc->data[2]->h);
	rayc->data[3]->img = mlx_xpm_file_to_image(rayc->ptr,
			map->ea, &rayc->data[3]->w, &rayc->data[3]->h);
	rayc->data[4]->img = mlx_xpm_file_to_image(rayc->ptr,
			map->we, &rayc->data[4]->w, &rayc->data[4]->h);
	if (!rayc->data[0]->img || !rayc->data[1]->img || !rayc->data[2]->img
		|| !rayc->data[4]->img || !rayc->data[3]->img)
	{
		printf("missing one or more texture\n");
		exit (1);
	}
	get_data_addr(rayc);
}

unsigned int	get_color(t_rayc *rayc, double wall, int x, int y)
{
	unsigned int	color;
	double			y_tex;
	double			x_tex;

	y_tex = ((double)rayc->ray_in_wall[y] * rayc->data[
			rayc->dir_tex]->w) / 50.0;
	x_tex = ((double)x * rayc->data[rayc->dir_tex]->h) / wall;
	color = my_mlx_pixel_get(rayc->data[rayc->dir_tex], x_tex, y_tex);
	return (color);
}

void	put_textures(t_rayc *rayc, t_txtr *txtr, int x)
{
	while (txtr->y < x * txtr->colom + txtr->colom)
	{
		txtr->distence = cos(rayc->radian[RAYS / 2] - rayc->radian[x]);
		txtr->distence = rayc->ray[x] * txtr->distence;
		txtr->wall = ((double)50 / txtr->distence) * (WINDOW_HIEGHT);
		txtr->i = (WINDOW_HIEGHT / 2) - (txtr->wall / 2);
		if (txtr->i < 0)
			txtr->i = 0;
		txtr->ws = ((WINDOW_HIEGHT / 2) - (txtr->wall / 2));
		draw_ceiling(rayc, txtr);
		while (txtr->inc < (int)txtr->wall && txtr->inc < WINDOW_HIEGHT)
		{
			get_wich_textures(rayc, x);
			txtr->color = get_color(rayc, txtr->wall,
					(txtr->inc + txtr->i) - txtr->ws, x);
			my_mlx_pixel_put(rayc->data[0],
				txtr->inc + txtr->i, txtr->y, txtr->color);
			txtr->inc++;
		}
		draw_floor(rayc, txtr);
		txtr->y++;
		txtr->inc = 0;
	}
}

void	the_wall(t_rayc *rayc)
{
	t_txtr	txtr;
	int		x;

	x = 0;
	txtr.inc = 0;
	txtr.colom = WINDOW_WIDTH / (double)RAYS;
	txtr.y = x * txtr.colom;
	rayc->data[0]->img = mlx_new_image(rayc->ptr, WINDOW_WIDTH, WINDOW_HIEGHT);
	rayc->data[0]->addr = mlx_get_data_addr(rayc->data[0]->img,
			&rayc->data[0]->bits_per_pixel, &rayc->data[0]->line_length,
			&rayc->data[0]->endian);
	while (x < (double)RAYS)
	{
		txtr.y = x * txtr.colom;
		put_textures(rayc, &txtr, x);
		x++;
	}
	mlx_put_image_to_window(rayc->ptr, rayc->window, rayc->data[0]->img, 0, 0);
	mlx_destroy_image(rayc->ptr, rayc->data[0]->img);
	while (x--)
		rayc->ray[x - 1] = 0;
}
