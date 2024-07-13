/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:31:03 by jaqribei          #+#    #+#             */
/*   Updated: 2024/07/10 18:23:32 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_longest_line_length(char **map)
{
	int		i;
	size_t	max;

	i = 0;
	max = ft_strlen(map[0]);
	while (map[i])
	{
		if (ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}

int	map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

char	*pad_line_to_length(char *line, int max_len)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = ft_calloc(sizeof(char), (max_len + 1));
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < max_len)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

int	hor_bordess(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != 32)
			{
				if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
				{
					ft_putstr_fd("Error\nMap is not valid", 1);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ver_borders(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != 32)
			{
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
				{
					ft_putstr_fd("Error\nMap is not valid", 1);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}
