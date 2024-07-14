/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:55:24 by jaqribei          #+#    #+#             */
/*   Updated: 2024/07/14 19:08:20 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_color_texture(char *line)
{
	while (ft_isspace(*line))
		line++;
	if ((!ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "NO", 2)
			|| !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "WE", 2))
		|| (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1)))
		return (1);
	return (0);
}

int	load_texture_list(t_game *d, t_texture_node **list)
{
	t_texture_node	*node;
	int				i;

	i = 0;
	while (d->texture2d[i])
	{
		node = new_node(d->texture2d[i++]);
		if (!node)
			return (0);
		append_texture_to_list(list, node);
	}
	return (1);
}

t_texture_node	*new_node(char *line)
{
	t_texture_node	*list;

	list = (t_texture_node *)ft_calloc(sizeof(t_texture_node), 1);
	if (!list)
		return (NULL);
	while (*line == ' ' || (*line >= 9 && *line <= 13))
		line++;
	if ((!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
			||!ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)))
	{
		list->key = ft_substr(line, 0, 2);
		list->value = ft_substr(line, get_index(line, 2), ft_strlen(line));
	}
	else if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
	{
		list->key = ft_substr(line, 0, 1);
		list->value = ft_substr(line, get_index(line, 1), ft_strlen(line));
	}
	list->next = NULL;
	return (list);
}

int	get_index(char *line, int i)
{
	while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
		i++;
	return (i);
}

void	append_texture_to_list(t_texture_node **list, t_texture_node *node)
{
	t_texture_node	*temp;

	temp = *list;
	if (*list == NULL)
	{
		(*list) = node;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = node;
}
