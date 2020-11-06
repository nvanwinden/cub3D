/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sprite.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 08:56:31 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/11/04 09:04:51 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Get colour from the current texture (vertical stripe)
** 256 and 128 factors to avoid floats
*/

void		put_pixels_sprite(t_game *game)
{
	int d;
	int y;

	y = game->sprite.draw_start_y;
	while (y < game->sprite.draw_end_y)
	{
		d = (y - game->sprite.screen_pos) * 256 -
		game->height * 128 + game->sprite.height * 128;
		game->tex[4].tex_y = ((d * game->tex[4].height) /
		game->sprite.height) / 256;
		game->tex[4].get_color = game->tex[4].addr +
		(game->tex[4].line_length * game->tex[4].tex_y +
		game->tex[4].tex_x * (game->tex[4].bits_per_pixel / 8));
		game->color = *(unsigned int*)game->tex[4].get_color;
		if (game->color != 0xFF000000 && game->color != 0)
			my_mlx_pixel_put(game, game->sprite.draw_start_x, y, game->color);
		y++;
	}
}

/*
** while loop: for every pixel (left to right),
** we're about to draw a vertical line
** tex_x is set to where on the texture you start pulling pixels from
** if statement:
** - if the sprite is ahead of you
** - if the sprite will not be off the screen (left)
** - if the sprite will not be off the screen (right)
** - if the sprite dist (ahead) is smaller than perp wall dist,
**   you know that the sprite is in front of a wall. If perp wall dist
**	 is smaller than sprite dist (ahead), you know the sprite is behind
**   a wall and should not be drawn.
*/

void		draw_sprite(t_game *game, double *z_buffer)
{
	while (game->sprite.draw_start_x < game->sprite.draw_end_x)
	{
		game->tex[4].tex_x = (int)(256 * (game->sprite.draw_start_x -
		(-game->sprite.width / 2 + game->sprite.center_x)) *
		game->tex[4].width / game->sprite.width) / 256;
		if (game->sprite.ahead_behind > 0 &&
			game->sprite.draw_start_x > 0 &&
			game->sprite.draw_start_x < game->width &&
			game->sprite.ahead_behind < z_buffer[game->sprite.draw_start_x])
			put_pixels_sprite(game);
		game->sprite.draw_start_x++;
	}
}
