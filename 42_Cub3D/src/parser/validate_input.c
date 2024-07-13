/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:52:53 by jaqribei          #+#    #+#             */
/*   Updated: 2024/07/05 16:17:48 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file_extension(char *file_name)
{
	if (!ft_strnstr(file_name, ".cub", ft_strlen(file_name)))
		exit(printf("ERROR: INVALID FILE EXTENSION"));
}

void	check_args(int argc, char **argv)
{
	if (argc != 2)
		exit(printf("ERROR: INVALID NUMBER OF ARGUMENTS"));
	check_file_extension(argv[1]);
}
