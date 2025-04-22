/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   201_setters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:46:43 by luigi             #+#    #+#             */
/*   Updated: 2025/03/14 18:38:28 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	assign_path(char *line, char *id, char **target, t_data *data)
{
	char	*new_line;

	if (line[0] == id[0] && line[1] == id[1])
	{
		line += 2;
		while (is_whitespace(*line))
			line++;
		line = ft_strtrim(line, "\n");
		new_line = ft_strtrim(line, " ");
		if (*line && *new_line)
		{
			*target = ft_strdup(new_line);
			return (free(new_line), free(line), SUCCESS);
		}
		else
			error(PARSE, data);
	}
	return (FAILURE);
}

void	set_coord(char *line, t_game *game, t_data *data)
{
	if (game->north.assigned == true && game->south.assigned == true
		&& game->west.assigned == true && game->east.assigned == true)
	{
		game->dup = true;
		return ;
	}
	if (assign_path(line, "NO", &game->north.path, data) == SUCCESS
		|| assign_path(line, "SO", &game->south.path, data) == SUCCESS
		|| assign_path(line, "WE", &game->west.path, data) == SUCCESS
		|| assign_path(line, "EA", &game->east.path, data) == SUCCESS)
	{
		if (*line == 'N' && game->north.assigned == false)
			game->north.assigned = true;
		else if (*line == 'S' && game->south.assigned == false)
			game->south.assigned = true;
		else if (*line == 'W' && game->west.assigned == false)
			game->west.assigned = true;
		else if (*line == 'E' && game->east.assigned == false)
			game->east.assigned = true;
		else
			game->dup = true;
		return ;
	}
	else
		error(PARSE, data);
}

int	set_floor(char *line, t_game *game, t_data *data)
{
	char	**rgb;
	int		i;

	line++;
	if (!is_whitespace(*line))
		error(PARSE, data);
	while (is_whitespace(*line))
		line++;
	if (!verify_comma_and_digit(line))
		return (FAILURE);
	if (line)
	{
		rgb = ft_split(line, ',');
		i = -1;
		while (++i <= 2)
			if (!rgb[i] || ft_strcmp(rgb[i], "\n") == 0)
				return (free_rgb(rgb), FAILURE);
		game->floor.r = ft_atoi(rgb[0]);
		game->floor.g = ft_atoi(rgb[1]);
		game->floor.b = ft_atoi(rgb[2]);
		free_rgb(rgb);
		return (SUCCESS);
	}
	else
		return (error(PARSE, data), FAILURE);
}

int	set_ceiling(char *line, t_game *game, t_data *data)
{
	char	**rgb;
	int		i;

	line++;
	if (!is_whitespace(*line))
		error(PARSE, data);
	while (is_whitespace(*line))
		line++;
	if (!verify_comma_and_digit(line))
		return (FAILURE);
	if (line)
	{
		rgb = ft_split(line, ',');
		i = -1;
		while (++i <= 2)
			if (!rgb[i] || ft_strcmp(rgb[i], "\n") == 0)
				return (free_rgb(rgb), FAILURE);
		game->ceiling.r = ft_atoi(rgb[0]);
		game->ceiling.g = ft_atoi(rgb[1]);
		game->ceiling.b = ft_atoi(rgb[2]);
		free_rgb(rgb);
		return (SUCCESS);
	}
	else
		return (error(PARSE, data), FAILURE);
}

int	set_map(char *line, t_map *map, t_data *data)
{
	static int	i = 0;

	if (!line)
		error(PARSE, data);
	if (!map->grid)
	{
		map->grid = malloc(sizeof(char *) * 1024);
		if (!map->grid)
			error(PARSE, data);
		ft_memset(map->grid, 0, sizeof(char *) * 1024);
	}
	map->grid[i++] = ft_strdup(line);
	return (SUCCESS);
}
