/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   900_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:04:49 by luigi             #+#    #+#             */
/*   Updated: 2025/02/13 15:26:40 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	error(int	no)
{
	if (no == PARSE)
		ft_putstr_fd("Error: Failure to parse map file\n", 2);
	else if (no == INIT_GAME)
		ft_putstr_fd("Error: Failure to initialize game\n", 2);
	else if (no == INIT_WINDOW)
		ft_putstr_fd("Error: Failure to initialize window\n", 2);
	else if (no == ARG)
		ft_putstr_fd("Error: Try ./cub3D <map.cub>\n", 2);
	else if (no == RGB)
		ft_putstr_fd("Error: Invalid or missing color\n", 2);
	else if (no == MAP)
		ft_putstr_fd("Error: Invalid character on map\n", 2);
	else if (no == PLAYER)
		ft_putstr_fd("Error: More than one or not enough players\n", 2);
	else if (no == TEXTURE)
		ft_putstr_fd("Error: Invalid texture\n", 2);
	//add frees !!!!!!!!!
	exit (no);
}
