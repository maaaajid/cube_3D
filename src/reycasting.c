/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 06:18:54 by aelbouaa          #+#    #+#             */
/*   Updated: 2023/11/30 22:21:23 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/Cub3D.h"

void	get_direction(t_rayc *rayc, int x)
{
	if (rayc->map[(int)(rayc->pp_y + (int)rayc->pre_inc_y[x] + 1) / 50]
		[(int)(rayc->pp_x + (int)rayc->pre_inc_x[x]) / 50] == '1')
	{
		rayc->dir[x] = 'S';
		rayc->ray_in_wall[x] = fmod(rayc->wallx, 50.0);
	}
	else if (rayc->map[(int)(rayc->pp_y + (int)rayc->pre_inc_y[x] - 1) / 50]
		[(int)(rayc->pp_x + (int)rayc->pre_inc_x[x]) / 50] == '1')
	{
		rayc->dir[x] = 'N';
		rayc->ray_in_wall[x] = fmod(rayc->wallx, 50.0);
	}
	else if (rayc->map[(int)(rayc->pp_y + (int)rayc->pre_inc_y[x]) / 50]
		[(int)(rayc->pp_x + (int)rayc->pre_inc_x[x] + 1) / 50] == '1')
	{
		rayc->dir[x] = 'E';
		rayc->ray_in_wall[x] = fmod(rayc->wally, 50.0);
	}
	else if (rayc->map[(int)(rayc->pp_y + (int)rayc->pre_inc_y[x]) / 50]
		[(int)(rayc->pp_x + (int)rayc->pre_inc_x[x] - 1) / 50] == '1')
	{
		rayc->dir[x] = 'W';
		rayc->ray_in_wall[x] = fmod(rayc->wally, 50.0);
	}
}

int	check_if_wall(t_rayc *rayc, int x)
{
	if (rayc->map[(int)(rayc->pp_y + (int)rayc->y_inc[x]) / 50]
		[(int)(rayc->pp_x + (int)rayc->x_inc[x]) / 50] != '0')
	{
		rayc->wallx = (rayc->pp_x + rayc->x_inc[x]);
		rayc->wally = (rayc->pp_y + rayc->y_inc[x]);
		get_direction(rayc, x);
		return (1);
	}
	return (0);
}

void	get_angel(t_rayc *rayc, int x)
{
	rayc->radian[x] = rayc->angel[x] * (3.141593 / 180);
	rayc->x_cos[x] = cos(rayc->radian[x]) * 2000000;
	rayc->y_sin[x] = sin(rayc->radian[x]) * 2000000;
	rayc->dx[x] = rayc->x_cos[x];
	rayc->dy[x] = rayc->y_sin[x];
	if (fabs(rayc->dx[x]) > fabs(rayc->dy[x]))
		rayc->steps[x] = fabs(rayc->dx[x]);
	else if (fabs(rayc->dx[x]) < fabs(rayc->dy[x]))
		rayc->steps[x] = fabs(rayc->dy[x]);
	else
	{
		if ((int)rayc->dx[x] > (int)rayc->dy[x])
			rayc->steps[x] = rayc->dx[x];
		else if ((int)rayc->dx[x] < (int)rayc->dy[x])
			rayc->steps[x] = rayc->dy[x];
		else if (fabs(rayc->dx[x]) == fabs(rayc->dy[x]))
			rayc->steps[x] = fabs(rayc->dx[x]);
	}
	rayc->x_inc[x] = rayc->dx[x] / rayc->steps[x];
	rayc->y_inc[x] = rayc->dy[x] / rayc->steps[x];
	rayc->x_inc[x] /= 5;
	rayc->y_inc[x] /= 5;
}

void	draw_rays(t_rayc *rayc)
{
	int		x;
	double	inc_x;
	double	inc_y;

	x = -1;
	while (++x < RAYS)
	{
		get_angel(rayc, x);
		inc_x = rayc->x_inc[x];
		inc_y = rayc->y_inc[x];
		while (fabs(rayc->y_inc[x]) < fabs(rayc->dy[x])
			|| fabs(rayc->x_inc[x]) < fabs(rayc->dx[x]))
		{
			rayc->pre_inc_x[x] = rayc->x_inc[x];
			rayc->pre_inc_y[x] = rayc->y_inc[x];
			rayc->y_inc[x] += inc_y;
			if (check_if_wall(rayc, x))
				break ;
			rayc->x_inc[x] += inc_x;
			if (check_if_wall(rayc, x))
				break ;
		}
		rayc->ray[x] = dist(rayc->pp_x, rayc->pp_y, rayc->wallx, rayc->wally);
	}
	the_wall(rayc);
}

void	forward(t_rayc *rayc)
{
	double	old_x_cos;
	double	old_y_sin;

	old_x_cos = rayc->x_cos[RAYS / 2];
	old_y_sin = rayc->y_sin[RAYS / 2];
	rayc->x_cos[RAYS / 2] = cos(rayc->radian[RAYS / 2]) * 6;
	rayc->y_sin[RAYS / 2] = sin(rayc->radian[RAYS / 2]) * 6;
	rayc->pp_x += (int)rayc->x_cos[RAYS / 2];
	rayc->pp_y += (int)rayc->y_sin[RAYS / 2];
	if (rayc->map[(int)(rayc->pp_y + rayc->y_sin[RAYS / 2]) / 50]
	[(int)rayc->pp_x / 50] != '1' && rayc->map[(int)rayc->pp_y / 50]
	[(int)(rayc->pp_x + rayc->x_cos[RAYS / 2]) / 50] != '1')
		draw_rays(rayc);
	else
		sliding(rayc, old_x_cos, old_y_sin);
}
