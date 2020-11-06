/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_game.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/25 19:06:48 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/11/06 18:19:16 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int				exit_game(void)
{
	exit(0);
}

static int		press(int keycode, t_game *game)
{
	if (keycode == W)
		game->key.w = 1;
	else if (keycode == A)
		game->key.a = 1;
	else if (keycode == S)
		game->key.s = 1;
	else if (keycode == D)
		game->key.d = 1;
	else if (keycode == LEFT)
		game->key.arrow_left = 1;
	else if (keycode == RIGHT)
		game->key.arrow_right = 1;
	if (keycode == ESC)
		exit(0);
	return (0);
}

static int		release(int keycode, t_game *game)
{
	if (keycode == W)
		game->key.w = 0;
	else if (keycode == A)
		game->key.a = 0;
	else if (keycode == S)
		game->key.s = 0;
	else if (keycode == D)
		game->key.d = 0;
	else if (keycode == LEFT)
		game->key.arrow_left = 0;
	else if (keycode == RIGHT)
		game->key.arrow_right = 0;
	return (0);
}

static int		get_game_map(t_game *game, t_cub *scene)
{
	game->map = ft_calloc(scene->line_count + 1, sizeof(char *));
	if (game->map == NULL)
		return (error("Malloc error for game_map\n"));
	while (game->y < scene->line_count)
	{
		game->x = 0;
		game->map[game->y] = ft_calloc(scene->longest_str + 1, sizeof(char));
		if (game->map[game->y] == NULL)
			return (error("Malloc error for game_map[]\n"));
		if (scene->map_str[game->i] == ',')
			game->i++;
		while (scene->map_str[game->i] != ',')
		{
			if (scene->map_str[game->i] == scene->cardinal_dir)
				set_dir_var(game, scene);
			else if (scene->map_str[game->i] == '2')
				game->num_sprite++;
			game->map[game->y][game->x] = scene->map_str[game->i];
			game->x++;
			game->i++;
		}
		game->map[game->y][game->x] = '\0';
		game->y++;
	}
	return (SUCCESS);
}

int				start_game(t_cub *scene)
{
	t_game		game;

	ft_bzero(&game, sizeof(t_game));
	get_game_map(&game, scene);
	get_sprite_pos(&game);
	init_game(&game, scene);
	mlx_hook(game.mlx.win, 2, 1L << 0, press, &game);
	mlx_hook(game.mlx.win, 3, 1L << 1, release, &game);
	mlx_hook(game.mlx.win, 17, 1L << 0, exit_game, &game);
	mlx_hook(game.mlx.win, 17, 1L << 2, exit_game, &game);
	if (scene->save_bmp == 1)
	{
		render_next_frame(&game);
		save_bmp(&game);
		exit(0);
	}
	mlx_loop_hook(game.mlx.mlx, render_next_frame, &game);
	mlx_loop(game.mlx.mlx);
	exit(0);
}
