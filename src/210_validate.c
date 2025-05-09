/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   210_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:27:45 by luigi             #+#    #+#             */
/*   Updated: 2025/03/13 00:01:46 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <string.h>

static unsigned long	convert_rgb_to_hex(t_color *color)
{
	unsigned long	hex;

	hex = ((color->r & 0xFF) << 16) + ((color->g & 0xFF) << 8) + (color->b & 0xFF);
	return (hex);
}

int	validate_textures(t_game *game)
{
	if (!game->north.path || !game->south.path || !game->west.path
		|| !game->east.path)
		return (FAILURE);
	if (check_texture(game->north.path) == FAILURE
		|| check_texture(game->south.path) == FAILURE
		|| check_texture(game->west.path) == FAILURE
		|| check_texture(game->east.path) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}

int	validate_rgb(t_game *game)
{
	if (game->floor.r == -1 || game->floor.g == -1 || game->floor.b == -1
		|| game->ceiling.r == -1 || game->ceiling.g == -1 || game->ceiling.b == -1)
		return (FAILURE);
	if (ft_isdigit(game->floor.r) && ft_isdigit(game->floor.g)
		&& ft_isdigit(game->floor.b) && ft_isdigit(game->ceiling.r)
		&& ft_isdigit(game->ceiling.g) && ft_isdigit(game->ceiling.b))
		return (FAILURE);
	if (!out_of_range(game))
		return (FAILURE);
	game->floor.hex = convert_rgb_to_hex(&game->floor);
	game->ceiling.hex = convert_rgb_to_hex(&game->ceiling);
	return (SUCCESS);
}

static int	verify_player(t_map *map, char c, int player_count)
{
	(void)player_count;
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		map->player_dir = c;
		return (SUCCESS);
	}
	return (FAILURE);
}

int	validate_rows(t_map *map, int y, t_data *data)
{
	int	x;
	int	player_count;

	player_count = 0;
	//fim da grid
	if (y >= map->height)
		return (FAILURE);
	if (map->grid[y] == NULL)
		return (FAILURE);
	
	//verificar largura, possible characters(6) e existencia de player
	while (map->grid[y])
	{
		x = -1;
		while (map->grid[y][++x] != '\n')
		{
			if (map->grid[y][x] != ' ' && map->grid[y][x] != '0'
				&& map->grid[y][x] != '1' && map->grid[y][x] != '\n')
			{
				if (!verify_player(map, map->grid[y][x], player_count++))
					return (FAILURE);
				else
				{
					map->player_x = x;
					map->player_y = y;
				}
			}
		}
		y++;
	}
	if (player_count != 1)
		error(PLAYER, data);
	return (SUCCESS);
}

//set coord
static int	set_map_coord(t_map *map)
{
	int		x;
	int		y;
	int		max_width;

	y = 0;
	if (!map->grid)
		return (FAILURE);
	while (map->grid[y])
		y++;
	map->height = y;
	y = 0;
	max_width = 0;
	while (map->grid[y])
	{
		x = 0;
		if (map->grid[y][x] == '\t')
			return(FAILURE);
		while (map->grid[y][x] && map->grid[y][x] != '\n')
			x++;
		if (x > max_width)
			max_width = x;
		y++;
	}
	map->width = max_width;
	return (SUCCESS);
}

static char	*create_border_line(int width)
{
	char	*line;
	int		i;

	line = malloc(sizeof(char) * (width + 1));
	if (!line)
		return (NULL);
	i = -1;
	while (++i < width)
		line[i] = '#';
	line[i] = '\0';
	return (line);
}

static void transform_map(char **map, int w)
{
    int  x, y;
    char *temp;

    y = 0;
    while (map[y])
    {
        x = 0;
        
        // Aloca memória nova
        temp = malloc(w + 1);
        if (!temp)
        {
            printf("Erro ao alocar memória para map[%d]\n", y);
            exit(EXIT_FAILURE);
        }
        ft_memset(temp, '#', w);  // Preenche com '#'
        temp[w] = '\0';

        // Copia os caracteres existentes até '\n' ou fim da string
        while (map[y][x] && map[y][x] != '\n' && x < w)
        {
            if (map[y][x] != ' ')
                temp[x] = map[y][x];
            x++;
        }

        free(map[y]);  // Libera a memória original
        map[y] = temp; // Substitui pelo novo buffer

        y++;
    }
    map[y] = NULL;
}

static char	**copy_map(t_map *map)
{
	char	**map_copy;
	int		i;
	int		new_height;
	int		new_widht;

	new_height = map->height + 2;
	new_widht = map->width + 2;
	map_copy = malloc(sizeof(char *) * (new_height + 1));
	if (!map_copy)
		return (NULL);
	map_copy[0] = create_border_line(new_widht);
	if (!map_copy[0])
		return (NULL);
	i = -1;
	while (++i < map->height)
	{
		map_copy[i + 1] = malloc(sizeof(char) * (new_widht + 1));
		if (!map_copy[i + 1])
			return (NULL);
		map_copy[i + 1][0] = '#';
		ft_strlcpy(&map_copy[i + 1][1], map->grid[i], map->width + 1);
	}
	map_copy[new_height - 1] = create_border_line(new_height);
	if (!map_copy[new_height - 1])
		return (NULL);
	map_copy[new_height] = NULL;
	transform_map(map_copy, new_widht);
	return (map_copy);
}

static int	validate_walls(t_map *map)
{
	char	**map_copy;
	int		i;

	map_copy = copy_map(map);
	i = -1;
	// while (map_copy[++i])
	// 	printf("%s\n", map_copy[i]);
	if (!map_copy)
		return (FAILURE);
	if (map->player_x < 0 || map->player_x >= map->width
		|| map->player_y < 0 || map->player_y >= map->height)
	{
		i = -1;
		while (map_copy[++i])
			free(map_copy[i]);
		free(map_copy);
		return (FAILURE);
	}
	//verificar os adjacentes do map_copy
	if (!check_map(map, map_copy))
		return (FAILURE);
	//dar free
	i = 0;
	while (map_copy[i])
		free(map_copy[i++]);
	free(map_copy);
	return (SUCCESS);
}

int	validate_map(t_map *map, t_data *data)
{
	//ver se mapa existe
	if (!set_map_coord(map))
		return (FAILURE);
	if (map->width <= 0 || map->height <= 0 || map->grid == NULL)
		return (FAILURE);
	//validar caracteres e verificar se o jogador existe
	if (!validate_rows(map, 0, data))
		return (FAILURE);
	//Varificar se o mapa esta rodeado de paredes, neste caso em cima e baixo (flood_fill)
	if (!validate_walls(map))
		return (FAILURE);
	return (SUCCESS);
}

int	_validate_data(t_game **game, t_data *data)
{
	//validar se as texturas existem
	if (!validate_textures(*game))
		error(TEXTURE, data);

	//validar se os rgb estao corretos
	if (!validate_rgb(*game))
		error(RGB, data);
	
	//validar se o mapa esta correto
	if (!validate_map((&(*game)->map), data))
		error(MAP, data);
	return (SUCCESS);
}
