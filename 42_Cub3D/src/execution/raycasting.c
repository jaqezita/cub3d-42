/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 04:35:29 by jaqribei          #+#    #+#             */
/*   Updated: 2024/07/15 00:40:50 by andrefil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_ray_intersections(t_mlx *mlx)
{
	double	intercept_h;
	double	intercept_v;
	int		ray;

	ray = 0;
	mlx->ray->ray_angle = mlx->player->angle - (mlx->player->fov_rad / 2);
	while (ray < SCREEN_WIDTH)
	{
		mlx->ray->flag = 0;
		intercept_h = calc_hor_intersec(mlx, norm_angle(mlx->ray->ray_angle));
		intercept_v = calc_ver_intersec(mlx, norm_angle(mlx->ray->ray_angle));
		if (intercept_v < intercept_h)
			mlx->ray->distance = intercept_v;
		else
		{
			mlx->ray->distance = intercept_h;
			mlx->ray->flag = 1;
		}
		render_wall(mlx, ray);
		ray++;
		mlx->ray->ray_angle += (mlx->player->fov_rad / SCREEN_WIDTH);
	}
}

float	calc_hor_intersec(t_mlx *mlx, float angle)
{
	float	ray_hor_x;
	float	ray_hor_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angle);
	ray_hor_y = floor(mlx->player->player_y / TILE_SIZE) * TILE_SIZE;
	pixel = adjust_intersec(angle, &ray_hor_y, &y_step, 1);
	ray_hor_x = mlx->player->player_x + (ray_hor_y - mlx->player->player_y) \
	/ tan(angle);
	if ((unit_circle(angle, 'y') && x_step > 0) \
	|| (!unit_circle(angle, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(ray_hor_x, ray_hor_y - pixel, mlx))
	{
		ray_hor_x += x_step;
		ray_hor_y += y_step;
	}
	mlx->ray->coord_h_x = ray_hor_x;
	mlx->ray->coord_h_y = ray_hor_y;
	return (sqrt(pow(ray_hor_x - mlx->player->player_x, 2) \
	+ pow(ray_hor_y - mlx->player->player_y, 2)));
}

float	calc_ver_intersec(t_mlx *mlx, float angle)
{
	float	ray_ver_x;
	float	ray_ver_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angle);
	ray_ver_x = floor(mlx->player->player_x / TILE_SIZE) * TILE_SIZE;
	pixel = adjust_intersec(angle, &ray_ver_x, &x_step, 0);
	ray_ver_y = mlx->player->player_y + (ray_ver_x - mlx->player->player_x) \
	* tan(angle);
	if ((unit_circle(angle, 'x') && y_step < 0) \
	|| (!unit_circle(angle, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(ray_ver_x - pixel, ray_ver_y, mlx))
	{
		ray_ver_x += x_step;
		ray_ver_y += y_step;
	}
	mlx->ray->coord_v_x = ray_ver_x;
	mlx->ray->coord_v_y = ray_ver_y;
	return (sqrt(pow(ray_ver_x - mlx->player->player_x, 2) \
	+ pow(ray_ver_y - mlx->player->player_y, 2)));
}

int	adjust_intersec(float angle, float *inter, float *step, int is_horizontal)
{
	if (is_horizontal)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > (M_PI / 2) && angle < 3 * (M_PI / 2)))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}
