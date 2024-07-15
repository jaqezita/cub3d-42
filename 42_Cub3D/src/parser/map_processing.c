/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:31:41 by jaqribei          #+#    #+#             */
/*   Updated: 2024/07/15 00:38:18 by andrefil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_map(t_game *maps)
{
	char	*temp;

	maps->map = ft_strdup("");
	while (maps->line)
	{
		if (maps->line[0] == '\n')
		{
			ft_putstr_fd("Error\nMap is not valid", 1);
			return (free_and_close(maps->map, maps->line, -1), NULL);
		}
		temp = maps->map;
		maps->map = ft_strjoin(maps->map, maps->line);
		free (temp);
		free (maps->line);
		maps->line = get_next_line(maps->fd);
	}
	return (maps->map);
}

int	read_map(char *argv, t_game *maps, int *count)
{
	char	*temp;

	maps->fd = open(argv, O_RDONLY);
	if (maps->fd == -1)
		return (ft_putstr_fd("Error\nFile not found", 1), 0);
	maps->line = get_next_line(maps->fd);
	if (!maps->line)
		return (ft_putstr_fd("Error\nFile is empty", 1), 0);
	maps->texture = ft_strdup("");
	while (maps->line && maps->line[0] != '1' && maps->line[0] != 32)
	{
		if (is_valid_color_texture(maps->line))
		{
			temp = maps->texture;
			maps->texture = ft_strjoin(maps->texture, maps->line);
			free (temp);
			(*count)++;
		}
		free(maps->line);
		maps->line = get_next_line(maps->fd);
	}
	if (!is_texture_color_count_valid(maps, *count))
		return (free_and_close(maps->map, NULL, maps->fd), 0);
	maps->texture2d = ft_split(maps->texture, '\n');
	if (!maps->texture2d)
		return (free_and_close(maps->texture, NULL, maps->fd), 0);
	if (!validate_map(maps, *count))
		return (free_and_close(maps->texture, NULL, maps->fd), \
				free_array(maps->texture2d), 0);
	return (free_and_close(maps->texture, maps->line, maps->fd), 1);
}

int	prepare_and_validate_map(t_game *d)
{
	int		i;
	size_t	max_len;

	max_len = get_longest_line_length(d->map_grid);
	i = 0;
	d->square_map = ft_calloc(sizeof(char *), map_height(d->map_grid) + 1);
	if (!d->square_map)
		return (0);
	while (d->map_grid[i])
	{
		if (max_len == (ft_strlen(d->map_grid[i])))
			d->square_map[i] = ft_strdup(d->map_grid[i]);
		else
			d->square_map[i] = pad_line_to_length(d->map_grid[i], max_len);
		i++;
	}
	d->square_map[i] = NULL;
	d->map_height = map_height(d->square_map);
	d->map_width = ft_strlen(d->square_map[0]);
	if (!hor_bordess(d->square_map) || !ver_borders(d->square_map))
		return (free_array(d->square_map), free_array(d->map_grid), \
		free_array (d->texture2d), 0);
	return (1);
}

int	is_texture_color_count_valid(t_game *maps, int count)
{
	if (count != 6)
	{
		ft_putstr_fd("Error\nTextures are not valid", 1);
		free(maps->texture);
		free(maps->line);
		return (0);
	}
	return (1);
}

void	calculate_map_dimensions(t_game *d)
{
	int	i;
	int	j;

	i = 0;
	while (d->map_grid[i])
	{
		j = 0;
		while (d->map_grid[i][j])
			j++;
		if (j > d->cols)
			d->cols = j;
		i++;
	}
	d->rows = i;
}
