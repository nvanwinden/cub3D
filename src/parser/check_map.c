/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 16:56:07 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/11/03 16:10:15 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int			check_chars(t_cub *scene, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("012NSEW ", line[i]))
			return (error("Error: invalid chars detected in map\n"));
		if (ft_strchr("NSEW", line[i]))
		{
			if (scene->cardinal_dir != 0)
				return (error("Error: multiple start pos in map\n"));
			scene->cardinal_dir = line[i];
		}
		i++;
	}
	return (SUCCESS);
}

static int	check_sides(t_cub *scene)
{
	if ((scene->map[scene->y][scene->x + 1] != '1' &&
	scene->map[scene->y][scene->x + 1] != 'x') ||
	(scene->map[scene->y][scene->x - 1] != '1' &&
	scene->map[scene->y][scene->x - 1] != 'x') ||
	(scene->map[scene->y + 1][scene->x] != '1' &&
	scene->map[scene->y + 1][scene->x] != 'x') ||
	(scene->map[scene->y - 1][scene->x] != '1' &&
	scene->map[scene->y - 1][scene->x] != 'x') ||
	(scene->map[scene->y + 1][scene->x + 1] != '1' &&
	scene->map[scene->y + 1][scene->x + 1] != 'x') ||
	(scene->map[scene->y + 1][scene->x - 1] != '1' &&
	scene->map[scene->y + 1][scene->x - 1] != 'x') ||
	(scene->map[scene->y - 1][scene->x + 1] != '1' &&
	scene->map[scene->y - 1][scene->x + 1] != 'x') ||
	(scene->map[scene->y - 1][scene->x - 1] != '1' &&
	scene->map[scene->y - 1][scene->x - 1] != 'x'))
		return (error("Error: invalid map, map is not closed\n"));
	return (SUCCESS);
}

int			check_map(t_cub *scene)
{
	scene->y = 0;
	scene->x = 0;
	while (scene->map[scene->y] != NULL)
	{
		while (scene->map[scene->y][scene->x])
		{
			if (scene->map[scene->y][scene->x] == 'x')
			{
				if (check_sides(scene) == ERROR)
					return (ERROR);
			}
			scene->x++;
		}
		scene->x = 0;
		scene->y++;
	}
	return (SUCCESS);
}
