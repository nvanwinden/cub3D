/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 11:24:25 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/11/04 15:28:09 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include "math.h"

# define SPACE 32
# define ERROR -1
# define SUCCESS 1

# define W 13
# define A 0
# define S 1
# define D 2

# define LEFT 123
# define RIGHT 124

# define ESC 53

# define UDIV 1
# define VDIV 1
# define VMOVE 0

# define MOVE_SPD .1222
# define ROT_SPD .1222

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_mlx;

typedef struct		s_key
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				arrow_left;
	int				arrow_right;
}					t_key;

typedef struct		s_bmp
{
	int				fd;
	int				file_size;
	int				*pix_array;
	char			*dest;
	int				y;
	int				x;
}					t_bmp;

typedef struct		s_texture
{
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	char			*get_color;
	int				width;
	int				height;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_texture;

typedef struct		s_sprite_pos
{
	double			x;
	double			y;
	double			dist;
}					t_sprite_pos;

typedef struct		s_sprite
{
	double			x;
	double			y;
	double			ahead_behind;
	double			right_left;
	int				center_x;
	double			inv;
	int				screen_pos;
	int				height;
	int				width;
	int				draw_start_y;
	int				draw_end_y;
	int				draw_start_x;
	int				draw_end_x;
}					t_sprite;

typedef struct		s_game
{
	t_mlx			mlx;
	t_bmp			bmp;
	t_texture		tex[5];
	t_key			key;
	t_sprite_pos	*sprite_pos;
	t_sprite		sprite;
	int				i;
	char			**map;
	int				width;
	int				height;
	int				floor;
	int				ceiling;
	int				save_flag;
	char			cardinal_dir;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	int				set_camera;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				x;
	int				y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	unsigned int	color;
	double			old_dir_x;
	double			old_plane_x;
	double			wall_x;
	int				d;
	int				num_sprite;
}					t_game;

typedef struct		s_id
{
	int				width;
	int				height;
	int				r;
	int				f;
	int				c;
}					t_id;

typedef struct		s_rgb
{
	int				r;
	int				g;
	int				b;
	int				count;
}					t_rgb;

typedef struct		s_id_flag
{
	int				r;
	int				f;
	int				c;
}					t_id_flag;

typedef	struct		s_cub
{
	int				fd;
	int				fd_flag;
	ssize_t			ret;
	char			*line;
	int				save_bmp;
	int				start_map;
	int				end_map;
	int				id_count;
	t_id_flag		type_id;
	char			**ptr;
	char			*no_tex_path;
	char			*so_tex_path;
	char			*we_tex_path;
	char			*ea_tex_path;
	char			*sprite_tex_path;
	char			cardinal_dir;
	char			*map_str;
	char			*tmp_line;
	char			*tmp_map;
	char			**map;
	int				map_i;
	int				y;
	int				x;
	int				longest_str;
	int				line_count;
	t_id			id_ptr;
	t_rgb			floor;
	t_rgb			ceiling;
	t_rgb			*rgb_ptr;
	int				startpos_x;
	int				startpos_y;
	char			wall;
	char			target;
	char			replacement;
}					t_cub;

int					error(char *message);
void				set_dir_var(t_game *game, t_cub *scene);
int					check_chars(t_cub *scene, char *line);
int					check_duplicates(t_cub *scene, char *line);
void				init_game(t_game *game, t_cub *scene);
void				move_player(t_game *game);
void				rotate_left(t_game *game);
void				rotate_right(t_game *game);
void				set_sprite(t_game *game, double *z_buffer);
void				my_mlx_pixel_put(t_game *game, int x, int y, int color);
int					save_bmp(t_game *game);
int					start_game(t_cub *scene);
int					render_next_frame(t_game *game);
int					parse_scene(t_cub *scene, char *line);
int					get_id_info(t_cub *scene, char *line);
int					get_map(t_cub *scene, char *line);
int					get_digit(char **line);
int					find_startpos(t_cub *scene);
void				get_line(t_cub *scene);
void				fill_line(t_cub *scene);
int					flood_fill(t_cub *scene, int x, int y);
int					check_map(t_cub *scene);
int					check_remaining_chars(char *line, char *type);
void				skip_space(char **line);
void				put_pixels(t_game *game);
int					set_texture(t_game *game, t_cub *scene);
void				set_tex_vars(t_game *game);
void				set_wall_height(t_game *game);
void				get_new_img(t_game *game);
int					get_sprite_pos(t_game *game);
void				sort_sprites(t_game *game);
void				draw_sprite(t_game *game, double *z_buffer);

#endif
