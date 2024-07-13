/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:31:44 by jaqribei          #+#    #+#             */
/*   Updated: 2024/07/13 20:35:16 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_wall(t_mlx *mlx, int ray)
{
	double	wall_height;
	double	wall_top_pix;
	double	wall_bottom_pix;
	double	vec_norm;

	vec_norm = norm_angle(mlx->ray->ray_angle - mlx->player->angle);
	mlx->ray->distance *= cos(vec_norm);
	wall_height = (TILE_SIZE / mlx->ray->distance) \
	* ((SCREEN_WIDTH / 2) / tan(mlx->player->fov_rad / 2));
	wall_bottom_pix = (SCREEN_HEIGHT / 2) + (wall_height / 2);
	wall_top_pix = (SCREEN_HEIGHT / 2) - (wall_height / 2);
	if (wall_bottom_pix > SCREEN_HEIGHT)
		wall_bottom_pix = SCREEN_HEIGHT;
	if (wall_top_pix < 0)
		wall_top_pix = 0;
	mlx->ray->index = ray;
	draw_tex(mlx, wall_top_pix, wall_bottom_pix, wall_height);
	render_floor_and_ceiling(mlx, ray, wall_top_pix, wall_bottom_pix);
}

void	draw_tex(t_mlx *mlx, int top_pix, int bottom_pix, double wall_height)
{
	double			x_offset;
	double			y_offset;
	mlx_texture_t	*tex;
	uint32_t		*pixels;
	double			factor;

	tex = get_texture(mlx, mlx->ray->flag);
	pixels = (uint32_t *)tex->pixels;
	factor = (double)tex->height / wall_height;
	x_offset = calc_x_offset(tex, mlx);
	y_offset = (top_pix - (SCREEN_HEIGHT / 2) + (wall_height / 2)) * factor;
	if (y_offset < 0)
		y_offset = 0;
	while (top_pix < bottom_pix)
	{
		put_pixel_bounds(mlx, mlx->ray->index, top_pix, \
		reverse_bytes(pixels[((int)y_offset * tex->width) + (int)x_offset]));
		y_offset += factor;
		top_pix++;
	}
}

void	render_floor_and_ceiling(t_mlx *mlx, int ray, int top_pix, int bot_pix)
{
	int	i;
	int	c;

	i = bot_pix;
	c = get_color(ft_atoi(mlx->data->flo_color[0]), \
	ft_atoi(mlx->data->flo_color[1]), ft_atoi(mlx->data->flo_color[2]), 255);
	while (i < SCREEN_HEIGHT)
		put_pixel_bounds(mlx, ray, i++, c);
	c = get_color(ft_atoi(mlx->data->roof_color[0]), \
	ft_atoi(mlx->data->roof_color[1]), ft_atoi(mlx->data->roof_color[2]), 255);
	i = 0;
	while (i < top_pix)
		put_pixel_bounds(mlx, ray, i++, c);
}

mlx_texture_t	*get_texture(t_mlx *mlx, int flag)
{
	mlx->ray->ray_angle = norm_angle(mlx->ray->ray_angle);
	if (flag == 0)
	{
		if (mlx->ray->ray_angle > M_PI / 2 && \
		mlx->ray->ray_angle < 3 * (M_PI / 2))
			return (mlx->texture->ea);
		else
			return (mlx->texture->we);
	}
	else
	{
		if (mlx->ray->ray_angle > 0 && mlx->ray->ray_angle < M_PI)
			return (mlx->texture->so);
		else
			return (mlx->texture->no);
	}
}

double	calc_x_offset(mlx_texture_t *tex, t_mlx *mlx)
{
	double	x_offset;

	if (mlx->ray->flag == 1)
		x_offset = (int)fmod(mlx->ray->coord_h_x * \
		(tex->width / TILE_SIZE), tex->width);
	else
		x_offset = (int)fmod(mlx->ray->coord_v_y * \
		(tex->width / TILE_SIZE), tex->width);
	return (x_offset);
}
