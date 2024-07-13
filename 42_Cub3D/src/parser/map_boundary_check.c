/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_boundary_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:02:03 by jaqribei          #+#    #+#             */
/*   Updated: 2024/07/10 17:19:29 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_boundaries(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

char	*find_last_line(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (map[i - 1]);
}

int	validate_map_lines(char **map)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (map[i])
	{
		if (!is_line_bordered_by_ones(map[i])
			|| !validate_map_chars(map[i], &flag) || flag > 1)
		{
			ft_putstr_fd("Error\nMap is not valid", 1);
			return (0);
		}
		i++;
	}
	if (flag == 0)
	{
		ft_putstr_fd("Error\nMap is not valid", 1);
		return (0);
	}
	return (1);
}

int	is_line_bordered_by_ones(char *line)
{
	while (ft_isspace(*line))
		line++;
	if (*line != '1' || line[ft_strlen(line) - 1] != '1')
		return (0);
	return (1);
}

int	validate_map_chars(char *line, int *flag)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] != '1' && line[i] != 32 && line[i] != '0'
				&& line[i] != '\n') && (line[i] != 'N' && line[i] != 'S'
				&& line[i] != 'W' && line[i] != 'E'))
			return (0);
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
			|| line[i] == 'E')
			(*flag)++;
		i++;
	}
	return (1);
}
