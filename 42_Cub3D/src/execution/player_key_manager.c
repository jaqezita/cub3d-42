/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_key_manager.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 04:30:50 by jaqribei          #+#    #+#             */
/*   Updated: 2024/07/13 04:31:40 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_press(mlx_key_data_t keydata, void *mlx_game)
{
	t_mlx	*mlx;

	mlx = mlx_game;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS \
	|| keydata.action == MLX_REPEAT))
		exit_game(mlx);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		mlx->player->left_right_flag = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		mlx->player->left_right_flag = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		mlx->player->up_down_flag = -1;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS))
		mlx->player->up_down_flag = 1;
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS))
		mlx->player->rotation_flag = -1;
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS))
		mlx->player->rotation_flag = 1;
	reset_keys(keydata, mlx);
}

void	reset_keys(mlx_key_data_t keydata, t_mlx *mlx)
{
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		mlx->player->left_right_flag = 0;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		mlx->player->left_right_flag = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		mlx->player->up_down_flag = 0;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		mlx->player->up_down_flag = 0;
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_RELEASE))
		mlx->player->rotation_flag = 0;
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_RELEASE))
		mlx->player->rotation_flag = 0;
}
