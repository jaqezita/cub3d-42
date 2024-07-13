/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:29:52 by jaqribei          #+#    #+#             */
/*   Updated: 2024/07/12 22:24:50 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_texture_colors(t_game *d, t_texture_node *list)
{
	t_texture_node	*temp;

	d->roof_color = NULL;
	d->flo_color = NULL;
	temp = list;
	while (temp)
	{
		if (!ft_strncmp(temp->key, "F", 1) || !ft_strncmp(temp->key, "C", 1))
		{
			if (!validate_rgb_values(ft_split(temp->value, ',')))
			{
				ft_putstr_fd("Error\ninvlid RGBA color\n", 1);
				return (0);
			}
			assign_texture_colors(temp, d);
		}
		temp = temp->next;
	}
	return (1);
}

int	validate_rgb_values(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return (free_array(rgb), 0);
		i++;
	}
	return (free_array(rgb), 1);
}	

void	assign_texture_colors(t_texture_node *temp, t_game *d)
{
	if (!ft_strncmp(temp->key, "F", 2))
	{
		d->flo_color = ft_split(temp->value, ',');
		return ;
	}
	else if (!ft_strncmp(temp->key, "C", 1))
	{
		d->roof_color = ft_split(temp->value, ',');
		return ;
	}
}

int	count_commas(char *rgb)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (rgb[i])
	{
		if (rgb[i++] == ',')
			count++;
	}
	return (count);
}

int	check_cf(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (ft_isspace(line[i]) || *line == 'F' || *line == 'C')
	{
		if (*line == 'F' || *line == 'C')
			flag++;
		line++;
	}
	if (flag != 1)
		return (0);
	if (!ft_isdigit(line[i]) && !ft_isdigit(line[(ft_strlen(line) - 1)]))
		return (0);
	while (line[i])
	{
		if ((!ft_isdigit(line[i]) && line[i] != ',')
			|| (line[i] == ',' && line[i + 1] && line[i + 1] == ','))
			return (0);
		i++;
	}
	return (1);
}
