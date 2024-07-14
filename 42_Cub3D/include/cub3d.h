/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:13:22 by jaqribei          #+#    #+#             */
/*   Updated: 2024/07/14 19:07:23 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include "../libs/libft/libft.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

# define SCREEN_WIDTH 1900
# define SCREEN_HEIGHT 1000
# define TILE_SIZE 30
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4

# define BLACK 0x000000FF
# define GREY 0x808080FF
# define BLUE 0x87CEEBFF
# define GREN 0x008000FF
# define ORANGE 0xFF9300FF
# define RED 0xFF0000FF
# define WHITE 0xFFFFFFFF

typedef struct s_texture
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}					t_texture;

typedef struct s_texture_node
{
	char					*key;
	char					*value;
	struct s_texture_node	*next;
}							t_texture_node;

typedef struct s_player
{
	int				player_x;
	int				player_y;
	double			angle;
	float			fov_rad;
	int				rotation_flag;
	int				left_right_flag;
	int				up_down_flag;
	int				mouse_x;
	int				mouse_y;
}					t_player;

typedef struct s_ray
{
	int				index;
	double			ray_angle;
	int				coord_h_x;
	int				coord_h_y;
	int				coord_v_x;
	int				coord_v_y;
	double			distance;
	int				flag;
}					t_ray;

typedef struct s_game
{
	char			**map_grid;
	int				rows;
	int				cols;
	int				p_x;
	int				p_y;
	int				map_width;
	int				map_height;
	char			**flo_color;
	char			**roof_color;
	int				fd;
	int				i;
	char			*line;
	char			*texture;
	char			*map;
	char			**texture2d;
	char			**square_map;
	char			**rgb;
	t_texture_node	*t;
}					t_game;

typedef struct s_mlx
{
	mlx_image_t		*img;
	mlx_t			*mlx;
	t_game			*data;
	t_ray			*ray;
	t_player		*player;
	t_texture		*texture;
	mouse_mode_t	mouse_mode;
	t_texture_node	*txtr;
}					t_mlx;

// ---parser---
//validate_input.c
void			check_file_extension(char *file_name);
void			check_args(int argc, char **argv);

//map_validation.c
int				is_valid_texture(char *line);
int				validate_map(t_game *maps, int count);
int				check_textures_isspace(char **texture, int count);
int				check_rgb(char **texture);
int				validate_map_boundaries(char **map);

//map_processing.c
char			*get_map(t_game *maps);
int				read_map(char *argv, t_game *maps, int *count);
int				prepare_and_validate_map(t_game *d);
int				is_texture_color_count_valid(t_game *maps, int count);
void			calculate_map_dimensions(t_game *d);

//map_boundary_check.c
int				check_map_boundaries(char *line);
char			*find_last_line(char **map);
int				validate_map_lines(char **map);
int				is_line_bordered_by_ones(char *line);
int				validate_map_chars(char *line, int *flag);

//map_utils
int				get_longest_line_length(char **map);
int				map_height(char **map);
char			*pad_line_to_length(char *line, int max_len);
int				hor_bordess(char **map);
int				ver_borders(char **map);

//texture_processing.c
int				is_valid_color_texture(char *line);
int				load_texture_list(t_game *d, t_texture_node **list);
t_texture_node	*new_node(char *line);
int				get_index(char *line, int i);
void			append_texture_to_list(t_texture_node **list, \
					t_texture_node *node);

//texture_utils.c
int				process_texture_colors(t_game *d, t_texture_node *list);
int				validate_rgb_values(char **rgb);
void			assign_texture_colors(t_texture_node *temp, t_game *d);
int				count_commas(char *rgb);
int				check_cf(char *line);

//cleanup.c
void			free_maps(t_game *maps);
void			free_texture_list(t_texture_node **list);
void			free_and_close(char *texture, char *line, int fd);
void			free_array(char **array);

//parser.c
int				parsing(int argc, char **argv, t_game *data, \
					t_texture_node *list);
int				check_duplicate(t_game *maps);
void			find_player_position(t_game *d);

// ---execution---
//execution.c
int				execute_game(t_game *game);
void			render_frame(void *mlx_game);
void			exit_game(t_mlx *mlx);

//raycasting
void			calc_ray_intersections(t_mlx *mlx);
float			calc_hor_intersec(t_mlx *mlx, float angle);
float			calc_ver_intersec(t_mlx *mlx, float angle);
int				adjust_intersec(float angle, float *inter, \
					float *step, int is_horizontal);

//raycasting_utils.c
int				unit_circle(float angle, char c);
int				wall_hit(float x, float y, t_mlx *mlx);
float			norm_angle(float angle);

//rendering
void			render_wall(t_mlx *mlx, int ray);
void			draw_tex(t_mlx *mlx, int top_pix, int bottom_pix, \
					double wall_height);
void			render_floor_and_ceiling(t_mlx *mlx, int ray, int top_pix, \
					int bot_pix);
mlx_texture_t	*get_texture(t_mlx *mlx, int flag);
double			calc_x_offset(mlx_texture_t *tex, t_mlx *mlx);

//rendering_utils.c
int				get_color(int r, int g, int b, int a);
void			put_pixel_bounds(t_mlx *mlx, int x, int y, int color);
int				reverse_bytes(int c);

//player.c
void			adjust_player_angle(t_mlx *mlx, int i);
void			update_player_position(t_mlx *mlx, double move_x, \
					double move_y);
void			set_player_info(t_mlx *mlx);
void			move_player(t_mlx *mlx, double move_x, double move_y);

//player_key_manager.c 
void			key_press(mlx_key_data_t keydata, void *mlx_game);
void			reset_keys(mlx_key_data_t keydata, t_mlx *mlx);


//texture_management.c
int				load_textures(t_texture *texture, t_texture_node *list);
int				validate_texture_loading(t_texture_node *list);
void			delete_tex(t_texture *texture);


//player movement
#endif