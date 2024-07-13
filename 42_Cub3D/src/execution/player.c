/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 04:25:20 by jaqribei          #+#    #+#             */
/*   Updated: 2024/07/13 04:34:24 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	adjust_player_angle(t_mlx *mlx, int i)
{
	if (i == 1)
	{
		mlx->player->angle += ROTATION_SPEED;
		if (mlx->player->angle > 2 * M_PI)
			mlx->player->angle -= 2 * M_PI;
	}
	else
	{
		mlx->player->angle -= ROTATION_SPEED;
		if (mlx->player->angle < 0)
			mlx->player->angle += 2 * M_PI;
	}
}

void	update_player_position(t_mlx *mlx, double move_x, double move_y)
{
	int	map_x;
	int	map_y;
	int	new_x;
	int	new_y;

	new_x = roundf(mlx->player->player_x + move_x);
	new_y = roundf(mlx->player->player_y + move_y);
	map_x = new_x / TILE_SIZE;
	map_y = new_y / TILE_SIZE;
	if (mlx->data->map_grid[map_y][map_x] != '1' && \
	(mlx->data->square_map[map_y][mlx->player->player_x / TILE_SIZE] != '1' && \
	mlx->data->square_map[mlx->player->player_y / TILE_SIZE][map_x] != '1'))
	{
		mlx->player->player_x = new_x;
		mlx->player->player_y = new_y;
	}
}

void	set_player_info(t_mlx *mlx)
{
	char	c;

	c = mlx->data->map_grid[mlx->data->p_y][mlx->data->p_x];
	if (c == 'N')
		mlx->player->angle = 3 * M_PI / 2;
	if (c == 'S')
		mlx->player->angle = M_PI / 2;
	if (c == 'E')
		mlx->player->angle = 0;
	if (c == 'W')
		mlx->player->angle = M_PI;
	mlx->player->player_x = (mlx->data->p_x * TILE_SIZE) + (TILE_SIZE / 2);
	mlx->player->player_y = (mlx->data->p_y * TILE_SIZE) + (TILE_SIZE / 2);
	mlx->player->fov_rad = FOV * (M_PI / 180);
}

void	move_player(t_mlx *mlx, double move_x, double move_y)
{
	if (mlx->player->rotation_flag == 1)
		adjust_player_angle(mlx, 1);
	if (mlx->player->rotation_flag == -1)
		adjust_player_angle(mlx, 0);
	if (mlx->player->left_right_flag == 1)
	{
		move_x = -sin(mlx->player->angle) * PLAYER_SPEED;
		move_y = cos(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->player->left_right_flag == -1)
	{
		move_x = sin(mlx->player->angle) * PLAYER_SPEED;
		move_y = -cos(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->player->up_down_flag == 1)
	{
		move_x = cos(mlx->player->angle) * PLAYER_SPEED;
		move_y = sin(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->player->up_down_flag == -1)
	{
		move_x = -cos(mlx->player->angle) * PLAYER_SPEED;
		move_y = -sin(mlx->player->angle) * PLAYER_SPEED;
	}
	update_player_position(mlx, move_x, move_y);
}
