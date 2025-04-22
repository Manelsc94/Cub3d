/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   110_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:36:24 by luigi             #+#    #+#             */
/*   Updated: 2025/03/14 18:37:08 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_player(t_player *player, t_map *map)
{
	player->x = (map->player_x + 0.5) * BLOCK;
	player->y = (map->player_y + 0.5) * BLOCK;
	if (map->player_dir == 'N')
		player->angle = 3 * PI / 2;
	else if (map->player_dir == 'S')
		player->angle = PI / 2;
	else if (map->player_dir == 'W')
		player->angle = PI;
	else if (map->player_dir == 'E')
		player->angle = 0;
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = -sin(player->angle) * 0.66;
	player->plane_y = cos(player->angle) * 0.66;
	player->key_w = false;
	player->key_s = false;
	player->key_a = false;
	player->key_d = false;
	player->key_left = false;
	player->key_right = false;
	player->key_shift = false;
	player->key_esc = false;
}

static int	verify_img(t_game *game)
{
	if (!game->north.img)
		return (FAILURE);
	if (!game->south.img)
		return (FAILURE);
	if (!game->east.img)
		return (FAILURE);
	if (!game->west.img)
		return (FAILURE);
	return (SUCCESS);
}

void	init_game(t_data *data)
{
	init_player(&data->player, &data->game->map);
	data->map = &data->game->map;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	data->data = data->img.addr;
	data->game->north.img = mlx_xpm_file_to_image(data->mlx,
			data->game->north.path, &data->game->north.w, &data->game->north.h);
	data->game->south.img = mlx_xpm_file_to_image(data->mlx,
			data->game->south.path, &data->game->south.w, &data->game->south.h);
	data->game->east.img = mlx_xpm_file_to_image(data->mlx,
			data->game->east.path, &data->game->east.w, &data->game->east.h);
	data->game->west.img = mlx_xpm_file_to_image(data->mlx,
			data->game->west.path, &data->game->west.w, &data->game->west.h);
	if (verify_img(data->game) == FAILURE)
	{
		game_exit(data);
		error(PARSE, data);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

static void	init_values(t_data *data)
{
	data->game->dup = false;
	data->game->north.path = NULL;
	data->game->south.path = NULL;
	data->game->east.path = NULL;
	data->game->west.path = NULL;
	data->game->north.assigned = false;
	data->game->south.assigned = false;
	data->game->east.assigned = false;
	data->game->west.assigned = false;
	data->game->floor.r = -1;
	data->game->floor.g = -1;
	data->game->floor.b = -1;
	data->game->ceiling.r = -1;
	data->game->ceiling.g = -1;
	data->game->ceiling.b = -1;
}

void	init_struct(t_data **data)
{
	*data = malloc(sizeof(t_data));
	ft_memset(*data, 0, sizeof(t_data));
	(*data)->game = malloc(sizeof(t_game));
	ft_memset((*data)->game, 0, sizeof(t_game));
	init_values(*data);
	(*data)->game->map.grid = NULL;
}
