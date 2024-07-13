/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 04:35:29 by jaqribei          #+#    #+#             */
/*   Updated: 2024/07/13 20:34:08 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < 3 * (M_PI / 2))
			return (1);
	}
	return (0);
}

int	wall_hit(float x, float y, t_mlx *mlx)
{
	int	map_x;
	int	map_y;

	if (x < 0 || y < 0)
		return (0);
	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (map_y >= mlx->data->map_height || map_x >= mlx->data->map_width)
		return (0);
	if (mlx->data->map_grid[map_y] && map_x <= \
	(int)ft_strlen(mlx->data->map_grid[map_y]))
		if (mlx->data->map_grid[map_y][map_x] == '1')
			return (0);
	return (1);
}

float	norm_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}
