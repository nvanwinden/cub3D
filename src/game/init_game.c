/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_game.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 08:42:32 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/11/06 18:26:56 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void		set_dir_var(t_game *game, t_cub *scene)
{
	if (scene->cardinal_dir == 'N')
		game->dir_x = -1;
	else if (scene->cardinal_dir == 'S')
		game->dir_x = 1;
	else if (scene->cardinal_dir == 'E')
		game->dir_y = 1;
	else if (scene->cardinal_dir == 'W')
		game->dir_y = -1;
	scene->map_str[game->i] = '0';
	if (scene->cardinal_dir == 'N' || scene->cardinal_dir == 'S')
		game->plane_y = 0.66;
	else if (scene->cardinal_dir == 'E' || scene->cardinal_dir == 'W')
		game->plane_x = 0.66;
	if (scene->cardinal_dir == 'S' || scene->cardinal_dir == 'W')
		game->set_camera = 1;
}

static int	rgb_to_hex(int r, int g, int b)
{
	int sum;

	r = r * pow(16, 4);
	g = g * pow(16, 2);
	sum = r + g + b;
	return (sum);
}

void		set_bmp_size(t_game *game, t_cub *scene)
{
	{
		if (scene->id_ptr.width > 16384)
			game->width = 16384;
		else
			game->width = scene->id_ptr.width;
		if (scene->id_ptr.height > 16384)
			game->height = 16384;
		else
			game->height = scene->id_ptr.height;
	}
}

static void	set_screen_size(t_game *game, t_cub *scene)
{
	int w;
	int	h;

	mlx_get_screen_size(game->mlx.mlx, &w, &h);
	if (scene->id_ptr.width > w)
		game->width = w;
	else
		game->width = scene->id_ptr.width;
	if (scene->id_ptr.height > h)
		game->height = h;
	else
		game->height = scene->id_ptr.height;
}

void		init_game(t_game *game, t_cub *scene)
{
	game->save_flag = scene->save_bmp;
	if (game->save_flag == 0)
		set_screen_size(game, scene);
	else
		set_bmp_size(game, scene);
	game->pos_x = scene->startpos_y + 0.5;
	game->pos_y = scene->startpos_x + 0.5;
	game->floor = rgb_to_hex(scene->floor.r, scene->floor.g, scene->floor.b);
	game->ceiling = rgb_to_hex(scene->ceiling.r,
	scene->ceiling.g, scene->ceiling.b);
	game->cardinal_dir = scene->cardinal_dir;
	game->mlx.mlx = mlx_init();
	game->mlx.win = mlx_new_window(game->mlx.mlx,
	game->width, game->height, "Cub3D");
	game->mlx.img = mlx_new_image(game->mlx.mlx, game->width, game->height);
	game->mlx.addr = mlx_get_data_addr(game->mlx.img,
	&game->mlx.bits_per_pixel, &game->mlx.line_length,
	&game->mlx.endian);
	set_texture(game, scene);
}
