/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   800_frees.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:56:15 by mde-agui          #+#    #+#             */
/*   Updated: 2025/03/14 17:56:47 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	clean_mlx_image(t_data *data)
{
	if (data->game->north.path && data->game->north.img)
		mlx_destroy_image(data->mlx, data->game->north.img);
	if (data->game->south.path && data->game->south.img)
		mlx_destroy_image(data->mlx, data->game->south.img);
	if (data->game->east.path && data->game->east.img)
		mlx_destroy_image(data->mlx, data->game->east.img);
	if (data->game->west.path && data->game->west.img)
		mlx_destroy_image(data->mlx, data->game->west.img);
	mlx_destroy_image(data->mlx, data->img.img);
}

int	game_exit(t_data *data)
{
	int		i;

	clean_mlx_image(data);
	free(data->game->north.path);
	free(data->game->south.path);
	free(data->game->east.path);
	free(data->game->west.path);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	free(data->mlx);
	if (data->game->map.grid)
	{
		i = 0;
		while (data->game->map.grid[i])
			free(data->game->map.grid[i++]);
		free(data->game->map.grid);
	}
	free(data->game);
	free(data);
	exit(0);
}

void	free_map(char **map)
{
	int		i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	free_rgb(char **rgb)
{
	int		i;

	if (!rgb)
		return ;
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
}
