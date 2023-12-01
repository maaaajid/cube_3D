/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 06:30:28 by aelbouaa          #+#    #+#             */
/*   Updated: 2023/11/29 15:12:53 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/Cub3D.h"

int	get_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int y, int x, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	my_mlx_pixel_get(t_data *data, int ytex, int xtex)
{
	void	*dst;

	dst = data->addr + (ytex * data->line_length + xtex * (
				data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int	player(int event, t_rayc *rayc)
{
	if (event == 119)
		forward(rayc);
	else if (event == 115)
		backwards(rayc);
	else if (event == 100)
		move_right(rayc);
	else if (event == 97)
		move_left(rayc);
	else if (event == 65363)
		rotete_right(rayc);
	else if (event == 65361)
		rotete_left(rayc);
	else if (event == 65307)
		exit(0);
	return (0);
}
