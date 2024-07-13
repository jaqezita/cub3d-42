/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:08:16 by jaqribei          #+#    #+#             */
/*   Updated: 2024/07/13 02:14:47 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_texture(char *line)
{
	while (*line == ' ' || (*line >= 9 && *line <= 13))
		(*line)++;
	if ((!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
			|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
		&& (line[2] == 32 || (line[2] >= 9 && line[2] <= 13)))
		return (1);
	else if ((!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
		&& (line[1] == 32 || (line[1] >= 9 && line[1] <= 13)))
		return (1);
	return (0);
}

int	validate_map(t_game *maps, int count)
{
	maps->map = get_map(maps);
	if (!maps->map)
		return (0);
	maps->map_grid = ft_split(maps->map, '\n');
	if (!maps->map_grid)
	{
		free(maps->map);
		return (0);
	}
	free(maps->map);
	if (!check_textures_isspace(maps->texture2d, count)
		|| !check_rgb(maps->texture2d) || !check_duplicate(maps)
		|| !validate_map_boundaries(maps->map_grid)
		|| !validate_map_lines(maps->map_grid))
	{
		free(maps->map_grid);
		return (0);
	}
	return (1);
}

int	check_textures_isspace(char **texture, int count)
{
	int	i;

	i = -1;
	if (count != 6)
		return (0);
	while (++i < count)
	{
		if (!is_valid_texture(texture[i]))
		{
			ft_putstr_fd("Error\nTextures are not valid", 1);
			return (0);
		}
	}
	return (1);
}

int	check_rgb(char **texture)
{
	int		i;
	char	*rgb;

	i = 0;
	while (texture[i])
	{
		rgb = texture[i];
		while (ft_isspace(*rgb))
			rgb++;
		if (rgb[0] == 'F' || rgb[0] == 'C')
		{
			if (count_commas(rgb) != 2 || !check_cf(rgb))
			{
				ft_putstr_fd("Error\nTextures are not valid", 1);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	validate_map_boundaries(char **map)
{
	if (!map[0])
	{
		ft_putstr_fd("Error\nMap is not valid", 1);
		return (0);
	}
	if (!check_map_boundaries(map[0])
		|| !check_map_boundaries(find_last_line(map)))
	{
		ft_putstr_fd("Error\nMap is not valid", 1);
		return (0);
	}
	return (1);
}
