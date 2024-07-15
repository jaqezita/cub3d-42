/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:57:32 by jaqribei          #+#    #+#             */
/*   Updated: 2024/07/14 23:43:17 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsing(int argc, char **argv, t_game *data, t_texture_node *list)
{
	int	count;

	list = NULL;
	check_args(argc, argv);
	count = 0;
	data->rows = 0;
	data->cols = 0;
	if (!read_map(argv[1], data, &count))
		return (0);
	if (!prepare_and_validate_map(data))
		return (0);
	if (!load_texture_list(data, &list))
		return (free_maps(data), free_texture_list(&list), 0);
	if (!process_texture_colors(data, list))
		return (free_maps(data), free_texture_list(&list), 0);
	find_player_position(data);
	calculate_map_dimensions(data);
	data->t = list;
	return (1);
}

int	check_duplicate(t_game *maps)
{
	int	i;
	int	j;

	i = 0;
	while (maps->texture2d[i])
	{
		j = i + 1;
		while (maps->texture2d[j])
		{
			if (!ft_strncmp(maps->texture2d[i], maps->texture2d[j], 2))
			{
				ft_putstr_fd("Error\nDuplicate textures", 1);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	find_player_position(t_game *d)
{
	int	i;
	int	j;

	i = 0;
	while (d->square_map[i])
	{
		j = 0;
		while (d->square_map[i][j])
		{
			if (d->square_map[i][j] == 'N' || d->square_map[i][j] == 'S'
				|| d->square_map[i][j] == 'W' || d->square_map[i][j] == 'E')
			{
				d->p_x = j;
				d->p_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}
