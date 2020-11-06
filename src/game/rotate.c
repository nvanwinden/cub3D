/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 17:06:30 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/11/03 09:13:17 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate_left(t_game *game)
{
	game->old_dir_x = game->dir_x;
	game->dir_x = game->dir_x * cos(ROT_SPD) -
	game->dir_y * sin(ROT_SPD);
	game->dir_y = game->old_dir_x * sin(ROT_SPD) +
	game->dir_y * cos(ROT_SPD);
	game->old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(ROT_SPD) -
	game->plane_y * sin(ROT_SPD);
	game->plane_y = game->old_plane_x * sin(ROT_SPD) +
	game->plane_y * cos(ROT_SPD);
}

void	rotate_right(t_game *game)
{
	game->old_dir_x = game->dir_x;
	game->dir_x = game->dir_x * cos(-ROT_SPD) -
	game->dir_y * sin(-ROT_SPD);
	game->dir_y = game->old_dir_x * sin(-ROT_SPD) +
	game->dir_y * cos(-ROT_SPD);
	game->old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(-ROT_SPD) -
	game->plane_y * sin(-ROT_SPD);
	game->plane_y = game->old_plane_x * sin(-ROT_SPD) +
	game->plane_y * cos(-ROT_SPD);
}
