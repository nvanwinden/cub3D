/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 12:50:50 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/11/06 17:03:00 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Follow the ray through the map until a wall is hit
** Using step, jump to next map square in x dir or y dir
*/

static void	find_wall(t_game *game)
{
	game->hit = 0;
	while (game->hit == 0)
	{
		if (game->side_dist_x < game->side_dist_y)
		{
			game->side_dist_x = game->side_dist_x + game->delta_dist_x;
			game->map_x = game->map_x + game->step_x;
			game->side = 0;
		}
		else
		{
			game->side_dist_y = game->side_dist_y + game->delta_dist_y;
			game->map_y = game->map_y + game->step_y;
			game->side = 1;
		}
		if (game->map[game->map_x][game->map_y] == '1')
			game->hit = 1;
	}
}

/*
** Step is the direction to move to follow the ray in the map
** up: game->step_x = -1
** down: game->step_x = 1;
** left: game->step_y = -1;
** right: game->step_y = 1;
** side_dist is the initial length from player
** to the first x and y side
*/

static void	set_side_dist(t_game *game)
{
	if (game->ray_dir_x < 0)
	{
		game->step_x = -1;
		game->side_dist_x = (game->pos_x - game->map_x) *
			game->delta_dist_x;
	}
	else
	{
		game->step_x = 1;
		game->side_dist_x = (game->map_x + 1.0 - game->pos_x) *
			game->delta_dist_x;
	}
	if (game->ray_dir_y < 0)
	{
		game->step_y = -1;
		game->side_dist_y = (game->pos_y - game->map_y) *
			game->delta_dist_y;
	}
	else
	{
		game->step_y = 1;
		game->side_dist_y = (game->map_y + 1.0 - game->pos_y) *
			game->delta_dist_y;
	}
}

/*
** Calculate delta_dist_x and delta_dist_y for that ray
** Delta dist is the distance between one x-side to the
** next and one y-side to the next
*/

static void	set_delta_dist(t_game *game)
{
	if (game->ray_dir_y == 0)
		game->delta_dist_x = 0;
	else if (game->ray_dir_x == 0)
		game->delta_dist_x = 1;
	else
		game->delta_dist_x = fabs(1 / game->ray_dir_x);
	if (game->ray_dir_x == 0)
		game->delta_dist_y = 0;
	else if (game->ray_dir_y == 0)
		game->delta_dist_y = 1;
	else
		game->delta_dist_y = fabs(1 / game->ray_dir_y);
}

/*
** camera_x: position on the camera plane (range -1 to 1)
** The larger the screen width, the more positions on the camera plane
** ray_dir: ray coordinates on camera plane from player position
** if dir is S/W (game->set_camera == 1), ray_dir should be reversed,
** otherwise everything is mirrored
** map_x and map_y represent the he current square of the map the ray is in
*/

static void	set_camera(t_game *game)
{
	game->camera_x = 2 * game->x / (double)game->width - 1;
	if (game->set_camera == 1)
	{
		game->ray_dir_x = game->dir_x + game->plane_x * -game->camera_x;
		game->ray_dir_y = game->dir_y + game->plane_y * -game->camera_x;
	}
	else
	{
		game->ray_dir_x = game->dir_x + game->plane_x * game->camera_x;
		game->ray_dir_y = game->dir_y + game->plane_y * game->camera_x;
	}
	game->map_x = (int)game->pos_x;
	game->map_y = (int)game->pos_y;
}

/*
** Render image and put image to window
** z_buffer holds the perpendicular wall distance from
** the camera plane to the wall (needed for sprites)
*/

int			render_next_frame(t_game *game)
{
	game->z_buffer = ft_calloc(game->width, sizeof(double));
	if (game->z_buffer == NULL)
		return (error("Malloc error: game->z_buffer"));
	game->x = 0;
	while (game->x < game->width)
	{
		set_camera(game);
		set_delta_dist(game);
		set_side_dist(game);
		find_wall(game);
		set_wall_height(game);
		set_tex_vars(game);
		put_pixels(game);
		game->z_buffer[game->x] = game->perp_wall_dist;
		game->x++;
	}
	set_sprite(game, game->z_buffer);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.img, 0, 0);
	if (game->save_flag == 0)
		get_new_img(game);
	move_player(game);
	return (SUCCESS);
}
