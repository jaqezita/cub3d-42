/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:37:34 by jaqribei          #+#    #+#             */
/*   Updated: 2024/07/13 20:38:08 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_textures(t_texture *texture, t_texture_node *list)
{
	t_texture_node	*tmp;

	tmp = list;
	if (!validate_texture_loading(list))
		return (0);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "NO", 2))
			texture->no = mlx_load_png(tmp->value);
		else if (!ft_strncmp(tmp->key, "SO", 2))
			texture->so = mlx_load_png(tmp->value);
		else if (!ft_strncmp(tmp->key, "WE", 2))
			texture->we = mlx_load_png(tmp->value);
		else if (!ft_strncmp(tmp->key, "EA", 2))
			texture->ea = mlx_load_png(tmp->value);
		tmp = tmp->next;
	}
	return (1);
}

int	validate_texture_loading(t_texture_node *list)
{
	t_texture_node	*tmp;
	mlx_texture_t	*texture;

	tmp = list;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "NO", 2) || !ft_strncmp(tmp->key, "SO", 2) \
		|| !ft_strncmp(tmp->key, "WE", 2) || !ft_strncmp(tmp->key, "EA", 2))
		{
			texture = mlx_load_png(tmp->value);
			if (!texture)
				return (0);
			mlx_delete_texture(texture);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	delete_tex(t_texture *texture)
{
	if (texture->no)
		mlx_delete_texture(texture->no);
	if (texture->so)
		mlx_delete_texture(texture->so);
	if (texture->we)
		mlx_delete_texture(texture->we);
	if (texture->ea)
		mlx_delete_texture(texture->ea);
}
