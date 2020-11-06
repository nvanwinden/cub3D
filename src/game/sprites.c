/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 13:36:48 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/11/06 16:52:47 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Set width of sprite relative to height and
** scale with ratio if width and height are not equal
*/

static void	set_sprite_width(t_game *game)
{
	game->sprite.width = (int)(game->sprite.height *
	((double)game->tex[4].width / (double)game->tex[4].height)) / UDIV;
	game->sprite.draw_start_x = -game->sprite.width / 2 + game->sprite.center_x;
	if (game->sprite.draw_start_x < 0)
		game->sprite.draw_start_x = 0;
	game->sprite.draw_end_x = game->sprite.width / 2 + game->sprite.center_x;
	if (game->sprite.draw_end_x >= game->width)
		game->sprite.draw_end_x = game->width - 1;
}

/*
** Set height of sprite on the screen, how long is the line going
** to be for drawing the sprite in pixels. The absolute value
** is the distance a negative number is away from zero. If the value
** is -5, the absolute distance is 5.
** This value will also be calculated if the sprite is behind you.
**
** Calculate lowest and highest pixel to fill in current stripe,
** starting top to bottom
*/

static void	set_sprite_height(t_game *game)
{
	game->sprite.height = abs((int)(game->height /
	(game->sprite.ahead_behind))) / VDIV;
	game->sprite.draw_start_y = game->height / 2 -
	game->sprite.height / 2 + game->sprite.screen_pos;
	if (game->sprite.draw_start_y < 0)
		game->sprite.draw_start_y = 0;
	game->sprite.draw_end_y = game->height / 2 +
	game->sprite.height / 2 + game->sprite.screen_pos;
	if (game->sprite.draw_end_y >= game->height)
		game->sprite.draw_end_y = game->height - 1;
}

/*
** Calculate pos of sprite relative to the player pos in map
** Ex: the sprite is 2 squares down and 1 quare left to the player
**
** Next, recalculate the sprite coordinates so they are relative to
** the direction that the player is looking. You are basically
** creating a new map with the player starting at (0.0)
**
** Check is sprite is ahead/behind you, and to left/right of you:
** - sprite to the left = -right_left
** - sprite to the right = +right_left
** - sprite in the middle = 0
** - sprite ahead = +ahead_behind
** - sprite behind = -ahead_behind
** - sprite in the middle = 0
**
** game->sprite.center_x is the pos of the sprite screen (x pixel)
** if sprite.center_x is 500 and your screen width is 1000,
** it means that the center of your sprite is exactly in
** the middle of the screen
**
** game->sprite.screen_pos changes the draw start and draw end,
** so you can draw the sprite higher or lower (hover effect)
*/

static void	modify_sprite_pos(t_game *game, int i)
{
	game->sprite.x = (game->sprite_pos[i].x) - game->pos_x;
	game->sprite.y = (game->sprite_pos[i].y) - game->pos_y;
	game->sprite.inv = 1.0 / (game->plane_x *
	game->dir_y - game->dir_x * game->plane_y);
	if (game->cardinal_dir == 'S' || game->cardinal_dir == 'W')
		game->sprite.right_left = (game->sprite.inv *
		(game->dir_y * game->sprite.x - game->dir_x *
		game->sprite.y) * -1);
	else
		game->sprite.right_left = game->sprite.inv *
		(game->dir_y * game->sprite.x - game->dir_x *
		game->sprite.y);
	game->sprite.ahead_behind = game->sprite.inv *
	(-game->plane_y * game->sprite.x + game->plane_x *
	game->sprite.y);
	game->sprite.center_x = (int)(game->width / 2) *
	(1 + game->sprite.right_left / game->sprite.ahead_behind);
	game->sprite.screen_pos = (int)(VMOVE / game->sprite.ahead_behind);
}

void		set_sprite(t_game *game, double *z_buffer)
{
	int	i;

	i = 0;
	sort_sprites(game);
	while (i < game->num_sprite)
	{
		modify_sprite_pos(game, i);
		set_sprite_height(game);
		set_sprite_width(game);
		draw_sprite(game, z_buffer);
		i++;
	}
	free(game->z_buffer);
}
