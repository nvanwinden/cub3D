/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 16:49:20 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/11/04 09:39:45 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Last if statement move functions: avoid player from
** hitting a wall (round number) by subtracting pos
** int from pos float so you get the fraction. Player
** bumps off a really small amount so they won't notice.
*/

static void	move_forward(t_game *game)
{
	if (game->map[(int)(game->pos_x + game->dir_x * MOVE_SPD)]
	[(int)(game->pos_y)] == '0')
		game->pos_x += game->dir_x * MOVE_SPD;
	if (game->map[(int)(game->pos_x)][(int)(game->pos_y +
	game->dir_y * MOVE_SPD)] == '0')
		game->pos_y += game->dir_y * MOVE_SPD;
	if (floor(game->pos_x - (int)game->pos_x) < 0.00000001 ||
		fabs(game->pos_y - (int)game->pos_y) < 0.00000001)
	{
		if (game->dir_x < 0)
			game->pos_x += .0001;
		else if (game->dir_x > 0)
			game->pos_x -= .0001;
		else if (game->dir_y < 0)
			game->pos_y += .0001;
		else if (game->dir_y > 0)
			game->pos_y -= .0001;
	}
}

static void	move_backward(t_game *game)
{
	if (game->map[(int)(game->pos_x - game->dir_x * MOVE_SPD)]
	[(int)(game->pos_y)] == '0')
		game->pos_x -= game->dir_x * MOVE_SPD;
	if (game->map[(int)(game->pos_x)][(int)(game->pos_y -
	game->dir_y * MOVE_SPD)] == '0')
		game->pos_y -= game->dir_y * MOVE_SPD;
	if (floor(game->pos_x - (int)game->pos_x) < 0.00000001 ||
		fabs(game->pos_y - (int)game->pos_y) < 0.00000001)
	{
		if (game->dir_x < 0)
			game->pos_x -= .0001;
		else if (game->dir_x > 0)
			game->pos_x += .0001;
		else if (game->dir_y < 0)
			game->pos_y -= .0001;
		else if (game->dir_y > 0)
			game->pos_y += .0001;
	}
}

static void	move_left(t_game *game)
{
	if (game->map[(int)(game->pos_x - game->dir_y * MOVE_SPD)]
	[(int)game->pos_y] == '0')
		game->pos_x = game->pos_x - game->dir_y * MOVE_SPD;
	if (game->map[(int)game->pos_x][(int)(game->pos_y -
	(-game->dir_x) * MOVE_SPD)] == '0')
		game->pos_y = game->pos_y - (-game->dir_x) * MOVE_SPD;
	if (floor(game->pos_y - (int)game->pos_y) < 0.00000001 ||
		fabs(game->pos_y - (int)game->pos_y) < 0.00000001)
	{
		if (game->dir_x < 0)
			game->pos_y += .0001;
		else if (game->dir_x > 0)
			game->pos_y -= .0001;
		else if (game->dir_y > 0)
			game->pos_x += .0001;
		else if (game->dir_y < 0)
			game->pos_x -= .0001;
	}
}

static void	move_right(t_game *game)
{
	if (game->map[(int)(game->pos_x + game->dir_y * MOVE_SPD)]
	[(int)game->pos_y] == '0')
		game->pos_x = game->pos_x + game->dir_y * MOVE_SPD;
	if (game->map[(int)(game->pos_x)][(int)(game->pos_y +
	(-game->dir_x) * MOVE_SPD)] == '0')
		game->pos_y = game->pos_y + (-game->dir_x) * MOVE_SPD;
	if (floor(game->pos_y - (int)game->pos_y) < 0.00000001 ||
		fabs(game->pos_y - (int)game->pos_y) < 0.00000001)
	{
		if (game->dir_x < 0)
			game->pos_y -= .0001;
		else if (game->dir_x > 0)
			game->pos_y += .0001;
		else if (game->dir_y > 0)
			game->pos_x -= .0001;
		else if (game->dir_y < 0)
			game->pos_x += .0001;
	}
}

void		move_player(t_game *game)
{
	if (game->key.w)
		move_forward(game);
	if (game->key.d)
		move_right(game);
	if (game->key.s)
		move_backward(game);
	if (game->key.a)
		move_left(game);
	if (game->key.arrow_left)
		rotate_left(game);
	if (game->key.arrow_right)
		rotate_right(game);
}
