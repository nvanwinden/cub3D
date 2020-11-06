/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_sprites.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 08:53:26 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/11/04 10:20:04 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	get_sprite_coordinates(t_game *game)
{
	game->sprite_pos[game->i].y = game->x + 0.5;
	game->sprite_pos[game->i].x = game->y + 0.5;
	game->i++;
}

int			get_sprite_pos(t_game *game)
{
	game->i = 0;
	game->y = 0;
	game->x = 0;
	if (game->num_sprite > 0)
	{
		game->sprite_pos = ft_calloc(game->num_sprite + 1,
		sizeof(t_sprite_pos));
		if (game->sprite_pos == NULL)
			return (error("Malloc error for game->sprite_pos\n"));
		while (game->map[game->y])
		{
			game->x = 0;
			while (game->map[game->y][game->x])
			{
				if (game->map[game->y][game->x] == '2')
					get_sprite_coordinates(game);
				game->x++;
			}
			game->y++;
		}
	}
	return (SUCCESS);
}

static void	swap(t_sprite_pos *num, t_sprite_pos *num1)
{
	t_sprite_pos	tmp;

	tmp = *num;
	*num = *num1;
	*num1 = tmp;
}

/*
** Sort sprites from furthest to closest
*/

static void	sort(t_game *game)
{
	int i;
	int j;
	int	max_idx;

	i = 0;
	while (i < game->num_sprite - 1)
	{
		max_idx = i;
		j = i + 1;
		while (j < game->num_sprite)
		{
			if (game->sprite_pos[j].dist > game->sprite_pos[max_idx].dist)
				max_idx = j;
			j++;
		}
		swap(&game->sprite_pos[max_idx], &game->sprite_pos[i]);
		i++;
	}
}

/*
** Calculate distance of each sprite relative to player pos
*/

void		sort_sprites(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_sprite)
	{
		game->sprite_pos[i].dist = ((game->pos_x - (game->sprite_pos[i].x)) *
		(game->pos_x - (game->sprite_pos[i].x)) + (game->pos_y -
		(game->sprite_pos[i].y)) * (game->pos_y - (game->sprite_pos[i].y)));
		i++;
	}
	sort(game);
}
