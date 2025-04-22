/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:44:23 by mde-agui          #+#    #+#             */
/*   Updated: 2025/03/14 19:28:48 by mde-agui         ###   ########.fr       */
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
# include <string.h>
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

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

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
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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
	bool		key_w;
	bool		key_s;
	bool		key_a;
	bool		key_d;
	bool		key_left;
	bool		key_right;
	bool		key_shift;
	bool		key_esc;
}			t_player;

//keys + events struct
typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*wall_t;
	t_img		img;
	t_game		*game;
	t_map		*map;
	t_player	player;
	char		*data;
}				t_data;

//texture struct
typedef struct s_texture
{
	char	*path;
	void	*img;
	int		w;
	int		h;
	bool	assigned;
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
	char	**grid;
	int		width;
	int		height;
	char	player_dir;
	int		player_x;
	int		player_y;
}			t_map;

//game struct
typedef struct s_game
{
	int			count;
	int			dup;
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
}				t_game;

typedef struct s_ray
{
	float			ray_x;
	float			ray_y;
	float			ray_dir_x;
	float			ray_dir_y;
	float			dist;
	float			angle_dif;
	int				height;
	int				draw_start;
	int				draw_end;
	int				y;
	int				tx_x;
	float			tx_y;
	char			*tx_addr;
	int				tx_bpp;
	int				tx_l;
	int				tx_endian;
	void			*tx_img;
	int				color;
	int				wall_dir;
	float			wall_x;
	float			prev_x;
	float			prev_y;
	int				prev_map_x;
	int				prev_map_y;
	int				map_x;
	int				map_y;

	float			tex_height;
	float			step;
	float			tex_pos;
	int				txpp;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	double			shade_factor;
	int				shade_r;
	int				shade_g;
	int				shade_b;
}				t_ray;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// Function prototypes

//110 - INIT
void			init_player(t_player *player, t_map *map);
void			init_game(t_data *data);
void			init_struct(t_data **data);

//200 - PARSER
bool			is_map(t_game *game);
int				init_game_struct(char *line, t_game *game, t_data *data);
int				sanity_check(char *file, char *type);
int				_parser(char *file, t_data *data, t_game *game);

//201 - SETTERS
int				assign_path(char *line, char *id, char **target, t_data *data);
void			set_coord(char *line, t_game *game, t_data *data);
int				set_floor(char *line, t_game *game, t_data *data);
int				set_ceiling(char *line, t_game *game, t_data *data);
int				set_map(char *line, t_map *map, t_data *data);

//202 - MISC
int				is_whitespace(char line);
unsigned long	convert_rgb_to_hex(t_color *color);
void			clear_image(t_data *data);
void			put_pixel(int x, int y, unsigned int color, t_data *data);

//210 - VALIDATE
int				verify_player(t_map *map, char c, int player_count);
int				_validate_data(t_game **game, t_data *data);
int				verify_comma_and_digit(char *line);

//211 - CHECKER
int				out_of_range(t_game *game);
int				check_texture(char *path);

//212 - CHECK MAP
int				check_holes(char **map_copy);
int				check_sides(char **map_copy);
int				check_bottom(char **map_copy);
int				check_top(char **map_copy);
int				check_map(t_map *map, char **map_copy);

//213 - VALIDATE TEXTURES
int				validate_textures(t_game *game);

//214 - VALIDATE RGB
int				validate_rgb(t_game *game);

//215 - VALIDATE MAP
int				validate_walls(t_map *map);
int				validate_rows(t_map *map, int y, t_data *data);
int				set_map_coord(t_map *map);
int				validate_map(t_map *map, t_data *data);

//216 - VALIDATE MISC
int				check_map_cell(t_map *map, int x, int y, int *player_count);
char			**copy_map(t_map *map);

//217 - CHECK MAP MISC
int				find_bottom_line(char **map_copy);
int				find_top_line(char **map_copy);
int				check_left_side(char **map_copy);
int				check_right_side(char **map_copy);

//300 - RAYCASTING
bool			touch_obs(float px, float py, t_data *data);
void			raycasting(t_ray *ray, float angle, t_data *data);
void			init_ray(t_ray *ray, t_player *player, float angle);
void			draw_line(t_player *player, float angle, int i, t_data *data);
int				raycaster_loop(t_data *data);

//301 - RAYCASTING CALCULATIONS
void			texture_coord(t_ray *ray);
void			determine_wall_hit_and_tx(t_ray *ray, t_data *data);
void			calc_wall_h_and_draw_range(t_ray *ray);
void			calc_dist_and_angle(t_ray *ray, t_player *player, float angle);
void			calc_whntx(t_ray *ray, t_player *pl, float angle, t_data *data);

//302 - RAYCASTING DRAWING
void			draw_floor(t_ray *ray, int i, t_data *data);
void			draw_wall(t_ray *ray, int i, t_data *data);
void			draw_ceiling(t_ray *ray, int i, t_data *data);

//303 - RAYCASTING TEXTURES
void			shader(t_ray *ray, int i, t_data *data);
void			determine_wall_dir(t_ray *ray);
void			select_texture(t_ray *ray, t_data *data);

//304 - RAYCASTING 2D
void			draw_square(int x, int y, int size, t_data *data);
void			draw_map(t_data *data);

//400 - PLAYER
void			update_direction_vectors(t_player *player);
void			rotate_player(t_player *player, float angle_speed);
void			move_player(t_player *player, t_data *data);

//401 - DIRECTION
void			move_right(t_player *player, t_data *data, float move_speed);
void			move_left(t_player *player, t_data *data, float move_speed);
void			move_backward(t_player *player, t_data *data, float move_speed);
void			move_forward(t_player *player, t_data *data, float move_speed);

//402 - KEYGEN
int				key_release(int keysim, t_player *player);
int				key_press(int keysim, t_player *player);

//800 - FREES
void			clean_mlx_image(t_data *data);
int				game_exit(t_data *data);
void			free_map(char **map);
void			free_rgb(char **rgb);

//900 - ERROR HANDLERS
void			error(int no, t_data *data);

#endif
