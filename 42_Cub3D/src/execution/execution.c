/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:29:44 by jaqribei          #+#    #+#             */
/*   Updated: 2024/07/15 00:39:22 by andrefil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	execute_game(t_game *game)
{
	t_mlx	mlx;

	if (SCREEN_HEIGHT > 1440 || SCREEN_WIDTH > 2560 || FOV >= 180 || FOV <= 0)
		return (free_texture_list(&game->t), free_maps(game), 0);
	mlx.player = (t_player *)ft_calloc(sizeof(t_player), 1);
	mlx.ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	mlx.texture = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	mlx.data = game;
	mlx.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", false);
	if (!mlx.mlx)
		return (exit_game(&mlx), 0);
	if (!load_textures(mlx.texture, game->t))
		return (exit_game(&mlx), 0);
	set_player_info(&mlx);
	mlx_key_hook(mlx.mlx, &key_press, &mlx);
	mlx_loop_hook(mlx.mlx, &render_frame, &mlx);
	mlx_loop(mlx.mlx);
	free(game->map);
	exit_game(&mlx);
	return (0);
}

void	render_frame(void *mlx_game)
{
	t_mlx	*mlx;

	mlx = mlx_game;
	mlx_delete_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	move_player(mlx, 0, 0);
	calc_ray_intersections(mlx);
	mlx_image_to_window(mlx->mlx, mlx->img, 0, 0);
}

void	exit_game(t_mlx *mlx)
{
	mlx_delete_image(mlx->mlx, mlx->img);
	mlx_close_window(mlx->mlx);
	free_texture_list(&mlx->data->t);
	free_maps(mlx->data);
	delete_tex(mlx->texture);
	free(mlx->texture);
	free(mlx->player);
	free(mlx->ray);
	mlx_terminate(mlx->mlx);
	mlx = 0;
	ft_putstr_fd("Exit Game\n", 1);
	exit(0);
}
