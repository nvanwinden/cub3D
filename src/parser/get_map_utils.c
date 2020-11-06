/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 16:36:19 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/11/04 10:27:11 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		flood_fill(t_cub *scene, int x, int y)
{
	scene->target = '0';
	scene->replacement = 'x';
	scene->wall = '1';
	if (scene->map[y][x] == scene->wall ||
	scene->map[y][x] == scene->replacement)
		return (0);
	if (scene->map[y][x] != scene->target &&
	scene->map[y][x] != scene->cardinal_dir &&
	scene->map[y][x] != '2')
		return (0);
	scene->map[y][x] = scene->replacement;
	flood_fill(scene, x, y + 1);
	flood_fill(scene, x, y - 1);
	flood_fill(scene, x + 1, y);
	flood_fill(scene, x - 1, y);
	return (0);
}

/*
** Fetch line from string and copy to 2D array
*/

void	get_line(t_cub *scene)
{
	if (scene->map_str[scene->map_i] == ',')
		scene->map_i++;
	while (scene->map_str[scene->map_i] != ',')
	{
		if (scene->x == 0)
		{
			scene->map[scene->y][scene->x] = '#';
			scene->x++;
		}
		scene->map[scene->y][scene->x] = scene->map_str[scene->map_i];
		scene->x++;
		scene->map_i++;
	}
	while (scene->x < scene->longest_str + 2)
	{
		scene->map[scene->y][scene->x] = '#';
		scene->x++;
	}
}

void	fill_line(t_cub *scene)
{
	while (scene->x < scene->longest_str + 2)
	{
		scene->map[scene->y][scene->x] = '#';
		scene->x++;
	}
}

int		find_startpos(t_cub *scene)
{
	scene->y = 0;
	while (scene->map[scene->y] != NULL)
	{
		while (scene->map[scene->y][scene->x])
		{
			if (scene->map[scene->y][scene->x] == scene->cardinal_dir)
			{
				scene->startpos_y = scene->y - 1;
				scene->startpos_x = scene->x - 1;
				return (SUCCESS);
			}
			scene->x++;
		}
		scene->y++;
		scene->x = 0;
	}
	return (SUCCESS);
}
