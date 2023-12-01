/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 06:13:56 by aelbouaa          #+#    #+#             */
/*   Updated: 2023/11/29 23:34:49 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/Cub3D.h"

void	backwards(t_rayc *rayc)
{
	double	old_x_cos;
	double	old_y_sin;

	old_x_cos = rayc->x_cos[RAYS / 2];
	old_y_sin = rayc->y_sin[RAYS / 2];
	rayc->x_cos[RAYS / 2] = cos(rayc->radian[RAYS / 2]) * 8;
	rayc->y_sin[RAYS / 2] = sin(rayc->radian[RAYS / 2]) * 8;
	rayc->pp_x -= (int)rayc->x_cos[RAYS / 2];
	rayc->pp_y -= (int)rayc->y_sin[RAYS / 2];
	if (rayc->map[(int)(rayc->pp_y - rayc->y_sin[RAYS / 2]) / 50]
	[(int)rayc->pp_x / 50] != '1' && rayc->map[(int)rayc->pp_y / 50]
	[(int)(rayc->pp_x - rayc->x_cos[RAYS / 2]) / 50] != '1')
		draw_rays(rayc);
	else
	{
		rayc->pp_x += (int)rayc->x_cos[RAYS / 2];
		rayc->pp_y += (int)rayc->y_sin[RAYS / 2];
		rayc->x_cos[RAYS / 2] = old_x_cos;
		rayc->y_sin[RAYS / 2] = old_y_sin;
	}
}

void	move_right(t_rayc *rayc)
{
	int		old_radian;
	double	old_x_cos;
	double	old_y_sin;

	old_x_cos = rayc->x_cos[RAYS / 2];
	old_y_sin = rayc->y_sin[RAYS / 2];
	old_radian = rayc->radian[RAYS / 2];
	rayc->radian[RAYS / 2] = (rayc->angel[RAYS / 2] + 90) * (3.141593 / 180);
	rayc->x_cos[RAYS / 2] = cos(rayc->radian[RAYS / 2]) * 8;
	rayc->y_sin[RAYS / 2] = sin(rayc->radian[RAYS / 2]) * 8;
	rayc->pp_x += (int)rayc->x_cos[RAYS / 2];
	rayc->pp_y += (int)rayc->y_sin[RAYS / 2];
	rayc->radian[RAYS / 2] = old_radian;
	if (rayc->map[(int)rayc->pp_y / 50]
		[(int)(rayc->pp_x + rayc->x_cos[RAYS / 2]) / 50] != '1'
		&& rayc->map[(int)(rayc->pp_y + rayc->y_sin[RAYS / 2]) / 50]
		[(int)rayc->pp_x / 50] != '1')
		draw_rays(rayc);
	else
	{
		rayc->pp_x -= (int)rayc->x_cos[RAYS / 2];
		rayc->pp_y -= (int)rayc->y_sin[RAYS / 2];
		rayc->x_cos[RAYS / 2] = old_x_cos;
		rayc->y_sin[RAYS / 2] = old_y_sin;
	}
}

void	move_left(t_rayc *rayc)
{
	int		old_radian;
	double	old_x_cos;
	double	old_y_sin;

	old_x_cos = rayc->x_cos[RAYS / 2];
	old_y_sin = rayc->y_sin[RAYS / 2];
	old_radian = rayc->radian[RAYS / 2];
	rayc->radian[RAYS / 2] = (rayc->angel[RAYS / 2] - 90) * (3.141593 / 180);
	rayc->x_cos[RAYS / 2] = cos(rayc->radian[RAYS / 2]) * 8;
	rayc->y_sin[RAYS / 2] = sin(rayc->radian[RAYS / 2]) * 8;
	rayc->pp_x += (int)rayc->x_cos[RAYS / 2];
	rayc->pp_y += (int)rayc->y_sin[RAYS / 2];
	rayc->radian[RAYS / 2] = old_radian;
	if (rayc->map[(int)rayc->pp_y / 50]
		[(int)(rayc->pp_x + rayc->x_cos[RAYS / 2]) / 50] != '1'
		&& rayc->map[(int)(rayc->pp_y + rayc->y_sin[RAYS / 2]) / 50]
		[(int)rayc->pp_x / 50] != '1')
		draw_rays(rayc);
	else
	{
		rayc->pp_x -= (int)rayc->x_cos[RAYS / 2];
		rayc->pp_y -= (int)rayc->y_sin[RAYS / 2];
		rayc->x_cos[RAYS / 2] = old_x_cos;
		rayc->y_sin[RAYS / 2] = old_y_sin;
	}
}

void	rotete_right(t_rayc *rayc)
{
	int	x;

	x = 0;
	while (x < RAYS)
	{
		rayc->angel[x] = rayc->angel[x] + 5;
		x++;
	}
	draw_rays(rayc);
}

void	rotete_left(t_rayc *rayc)
{
	int	x;

	x = 0;
	while (x < RAYS)
	{
		rayc->angel[x] = rayc->angel[x] - 5;
		x++;
	}
	draw_rays(rayc);
}
