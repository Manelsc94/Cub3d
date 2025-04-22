/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:44:23 by mde-agui          #+#    #+#             */
/*   Updated: 2025/03/13 15:12:41 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include "../lib/mlx/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <X11/keysym.h>
# include "../lib/libft/libft_42/libft.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */

# define WIDTH 1280
# define HEIGHT 720
# define FOV 60
# define BLOCK 64
# define ROTATE_SPEED 0.07
# define PI 3.14159265359
# define TWO_D 0

# define NORTH -> PI / 2
# define SOUTH -> 3 * PI / 2
# define WEST -> PI
# define EAST -> PI * 2

/* ************************************************************************** */
/*                                  ENUMS								  	  */
/* ************************************************************************** */

//Cub3D Status
typedef enum e_status
{
	FAILURE,
	SUCCESS
}	t_status;

//Error Handlers
typedef enum e_error
{
	ARG,
	RGB,
	MAP,
	PARSE,
	PLAYER,
	TEXTURE,
	VALIDATE,
	INIT_GAME,
	INIT_WINDOW,
}	t_error;

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

typedef struct s_game		t_game;
typedef struct s_map		t_map;

//image struct
typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}			t_img;

//player struct -> coord
typedef struct s_player
{
    float		x;
    float		y;
    float		angle;
    double		dir_x;
    double		dir_y;
    double		plane_x;
    double		plane_y;
	bool        key_w;
    bool        key_s;
    bool        key_a;
    bool        key_d;
    bool        key_left;
    bool        key_right;
    bool        key_shift;
    bool        key_esc;
}			t_player;

//keys + events struct
typedef struct s_data
{
    void		*mlx;
    void		*win;
    void		*wall_t;
    t_img		img;
    t_game      *game;
    t_map       *map;
    t_player    player;
	char		*data;
}				t_data;

//texture struct
typedef struct s_texture
{
    char    *path;
    void    *img;
    int     width;
    int     height;
}			t_texture;

//colour struct
typedef struct s_color
{
    int				r;
    int				g;
    int				b;
	unsigned long	hex;
}		t_color;

//map struct
typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
    char    player_dir;  // N, S, E, or W
    int     player_x;
    int     player_y;
}			t_map;

//game struct
typedef struct s_game
{
	int			count;
	int			dup;
    t_texture   north;
    t_texture   south;
    t_texture   west;
    t_texture   east;
    t_color     floor;
    t_color     ceiling;
    t_map       map;
}				t_game;

typedef struct s_ray
{
	float	ray_x;
	float	ray_y;
	float	ray_dir_x; // Calculate ray direction x-component
	float	ray_dir_y; // Calculate ray direction y-component
	float	dist;
	float	angle_dif;
	int		height;
	int		draw_start;
	int		draw_end;
	int		y;
	int		tx_x;
	float	tx_y; // Changed to float for smoother texture stepping
	char	*tx_addr;
	int		tx_bpp;
	int		tx_l;
	int		tx_endian;
	void	*tx_img;
	int		color;
	int		wall_dir; // 0=north, 1=south, 2=east, 3=west
	float	wall_x;   // Where exactly the wall was hit
    float   prev_x;
    float   prev_y;
    int     prev_map_x;
    int     prev_map_y;
    int     map_x;
    int     map_y;

    float   tex_height;
    float   step;
    float   tex_pos;
    int     txpp;
    unsigned char r;
    unsigned char g;
    unsigned char b;

    double shade_factor;
    int shade_r;
    int shade_g;
    int shade_b;
}				t_ray;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// Function prototypes

//110 - INIT
void	init_struct(t_data **data);

//200 - PARSER
int		_parser(char *file, t_data *data, t_game *game);
int		init_game_struct(char *line, t_game *game, t_data *data);
int		sanity_check(char *file, char *type);

//201 - SETTERS
int		is_whitespace(char line);
int		assign_path(char *line, char *id, char **target, t_data *data);
int		set_map(char *line, t_map *map, t_data *data);
void	set_fc(char *line, t_game *game, t_data *data);
void	set_coord(char *line, t_game *game, t_data *data);

//210 - VALIDATE
int		_validate_data(t_game **game, t_data *data);
int		validate_textures(t_game *game);
int		validate_rgb(t_game *game);
int		validate_map(t_map *map, t_data *data);
int		validate_rows(t_map *map, int y, t_data *data);

//211 - CHECKER
int		check_texture(char *path);
int		out_of_range(t_game *game);

//212 - CHECK MAP
int		check_map(t_map *map, char **map_copy);
int		check_top(t_map *map, char **map_copy);
int		check_bottom(t_map *map, char **map_copy);
int		check_sides(t_map *map, char **map_copy);
int		check_holes(t_map *map, char **map_copy);

//300 - RAYCASTING
void	put_pixel(int x, int y, unsigned int color, t_data *data);
bool	touch_obs(float px, float py, t_data *data);
float	fixed_dist(float x1, float y1, float x2, t_data *data);
void	draw_line(t_player *player, float angle, int i, t_data *data);
void	draw_square(int x, int y, int size, t_data *data);
void	draw_map(t_data *data);
void	clear_image(t_data *data);
int		draw_loop(t_data *data);

//400 - PLAYER
void	init_player(t_player *player, t_map *map);
int		key_press(int keysim, t_player *player);
int		key_release(int keysim, t_player *player);
void	rotate_player(t_player *player, float angle_speed);
int		game_exit(t_data *data);

//void	move_player_position(t_player *player, int speed, float cos_angle, float sin_angle);
void	move_player(t_player *player, t_data *data);

//900 - ERROR HANDLERS
void	error(int	no, t_data *data);

#endif
