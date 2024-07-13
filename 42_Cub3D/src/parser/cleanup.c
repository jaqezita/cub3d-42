/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:51:33 by jaqribei          #+#    #+#             */
/*   Updated: 2024/07/12 22:24:50 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_maps(t_game *maps)
{
	free_array(maps->map_grid);
	free_array(maps->square_map);
	free_array(maps->texture2d);
	if (maps->flo_color)
		free_array(maps->flo_color);
	if (maps->roof_color)
		free_array(maps->roof_color);
}

void	free_texture_list(t_texture_node **list)
{
	t_texture_node	*tmp;

	tmp = *list;
	while (tmp)
	{
		*list = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = *list;
	}
	free(*list);
}

void	free_and_close(char *texture, char *line, int fd)
{
	if (texture)
		free(texture);
	if (line)
		free(line);
	if (fd > 0)
		close (fd);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
