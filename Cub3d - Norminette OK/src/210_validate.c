/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   210_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:27:45 by luigi             #+#    #+#             */
/*   Updated: 2025/03/14 18:31:11 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	verify_player(t_map *map, char c, int player_count)
{
	(void)player_count;
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		map->player_dir = c;
		return (SUCCESS);
	}
	return (FAILURE);
}

int	_validate_data(t_game **game, t_data *data)
{
	if (!validate_textures(*game) || (*game)->dup == true)
		error(TEXTURE, data);
	if (!validate_rgb(*game))
		error(RGB, data);
	if (!validate_map((&(*game)->map), data))
		error(MAP, data);
	return (SUCCESS);
}

int	verify_comma_and_digit(char *line)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (line[++i])
		if (line[i] == ',')
			count++;
	if (count > 3)
		return (FAILURE);
	i = -1;
	while (line[++i] != '\n')
	{
		while (line[i] == ' ' || line[i] == ',')
			i++;
		if (line[i] == '\n')
			break ;
		if (!ft_isdigit(line[i]))
			return (FAILURE);
	}
	return (SUCCESS);
}
