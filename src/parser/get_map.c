/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 16:27:58 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/11/03 18:33:45 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Find longest string in the map
*/

static int	get_longest_string(t_cub *scene)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (scene->map_str[i])
	{
		while (scene->map_str[i] != ',')
		{
			i++;
			j++;
		}
		if (j > count)
			count = j;
		j = 0;
		i++;
	}
	return (count);
}

/*
** Create map in 2D array, prepare for flood fill
*/

static int	map_array(t_cub *scene)
{
	scene->map = ft_calloc(scene->line_count + 3, sizeof(char*));
	if (scene->map == NULL)
		return (error("Malloc error: scene->map\n"));
	scene->longest_str = get_longest_string(scene);
	while (scene->y < scene->line_count + 2)
	{
		scene->x = 0;
		scene->map[scene->y] = ft_calloc(scene->longest_str + 3, sizeof(char));
		if (scene->map == NULL)
			return (error("Malloc error: scene->map\n"));
		if (scene->y == 0)
			fill_line(scene);
		if (scene->y > 0 && scene->y != scene->line_count + 1)
			get_line(scene);
		if (scene->y == scene->line_count + 1)
			fill_line(scene);
		scene->map[scene->y][scene->x] = '\0';
		scene->y++;
	}
	find_startpos(scene);
	flood_fill(scene, scene->x, scene->y);
	return (check_map(scene));
}

/*
** Add map to one string, seperated by commas
*/

static int	join_line(t_cub *scene, char *line)
{
	scene->start_map = 1;
	if (scene->map_str == NULL)
		scene->map_str = ft_strdup("");
	if (scene->map_str == NULL)
		return (error("Malloc error: scene->map_str\n"));
	scene->tmp_line = ft_calloc(ft_strlen(line) + 2, sizeof(char));
	if (scene->tmp_line == NULL)
		return (error("Malloc error: scene->tmp_line\n"));
	ft_strlcpy(scene->tmp_line, line, ft_strlen(line) + 1);
	scene->tmp_line[ft_strlen(line)] = ',';
	scene->tmp_line[ft_strlen(line) + 1] = '\0';
	scene->tmp_map = ft_strdup(scene->map_str);
	if (scene->tmp_map == NULL)
		return (error("Malloc error: scene->tmp_map\n"));
	free(scene->map_str);
	scene->map_str = ft_strjoin(scene->tmp_map, scene->tmp_line);
	if (scene->map_str == NULL)
		return (error("Malloc error: scene->map_str\n"));
	free(scene->tmp_line);
	scene->tmp_line = NULL;
	free(scene->tmp_map);
	scene->tmp_map = NULL;
	return (SUCCESS);
}

/*
** Fetch map from .cub file
*/

int			get_map(t_cub *scene, char *line)
{
	int		i;

	i = 0;
	if (check_chars(scene, line) == ERROR)
		return (ERROR);
	else if (scene->ret == 0 && *line == '\0' && scene->start_map == 1)
	{
		if (scene->cardinal_dir == 0)
			return (error("No cardinal direction found\n"));
		return (map_array(scene));
	}
	if (ft_strchr("012NSEW ", line[i]))
	{
		join_line(scene, line);
		scene->line_count++;
		if (scene->ret == 0)
		{
			if (scene->cardinal_dir == 0)
				return (error("No cardinal direction found\n"));
			return (map_array(scene));
		}
	}
	else
		return (error("Invalid map\n"));
	return (SUCCESS);
}
