/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_id_info.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 15:22:28 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/11/04 13:37:24 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	set_tex_path(t_cub *scene, char *line)
{
	int		i;

	i = 0;
	if (!ft_strncmp(line, "NO", 2))
		scene->ptr = &scene->no_tex_path;
	else if (!ft_strncmp(line, "SO", 2))
		scene->ptr = &scene->so_tex_path;
	else if (!ft_strncmp(line, "WE", 2))
		scene->ptr = &scene->we_tex_path;
	else if (!ft_strncmp(line, "EA", 2))
		scene->ptr = &scene->ea_tex_path;
	else if (!ft_strncmp(line, "S", 1))
		scene->ptr = &scene->sprite_tex_path;
	while (ft_isalpha(*line))
		line++;
	skip_space(&line);
	while (ft_isprint(line[i]) && line[i] != '\0')
		i++;
	*scene->ptr = ft_substr(line, 0, i);
	if (*scene->ptr == NULL)
		return (error("Malloc error: unable to set texture path\n"));
	else if (ft_strncmp(*scene->ptr + (ft_strlen(*scene->ptr) - 4), ".xpm", 4))
		return (error("Error: tex path should have .xpm extension\n"));
	return (check_remaining_chars(line + i, "P"));
}

static int	set_digit_rgb(t_cub *scene, char **line, int *ptr)
{
	scene->rgb_ptr->count++;
	skip_space(line);
	if (ft_isdigit(**line) == 0)
		return (ERROR);
	while (ft_isdigit(**line))
	{
		*ptr = (*ptr * 10) + (**line - '0');
		(*line)++;
	}
	if (*ptr < 0 || *ptr > 255)
		return (ERROR);
	skip_space(line);
	if (scene->rgb_ptr->count == 3)
		return (SUCCESS);
	if (**line == ',')
		(*line)++;
	else
		return (ERROR);
	return (SUCCESS);
}

static int	get_rgb_colour(t_cub *scene, char *line, char *type)
{
	line++;
	skip_space(&line);
	if (ft_isdigit(*line))
	{
		if (set_digit_rgb(scene, &line, &scene->rgb_ptr->r) == SUCCESS)
		{
			if (set_digit_rgb(scene, &line, &scene->rgb_ptr->g) == SUCCESS)
			{
				if (set_digit_rgb(scene, &line, &scene->rgb_ptr->b) == SUCCESS)
					return (check_remaining_chars(line, type));
			}
		}
	}
	if (type[0] == 'F')
		return (error("Error: invalid floor colour\n"));
	else if (type[0] == 'C')
		return (error("Error: invalid ceiling colour\n"));
	return (SUCCESS);
}

static int	set_screen_res(char *line, t_cub *scene)
{
	scene->type_id.r = 1;
	line++;
	skip_space(&line);
	if (!ft_isdigit(*line))
		return (error("Error: invalid value for screen width\n"));
	scene->id_ptr.width = get_digit(&line);
	if (scene->id_ptr.width == 0)
		return (error("Error: invalid value for screen width\n"));
	if (*line != SPACE)
		return (error("Error: no screen height detected\n"));
	skip_space(&line);
	if (!ft_isdigit(*line))
		return (error("Error: invalid value for screen height\n"));
	scene->id_ptr.height = get_digit(&line);
	if (scene->id_ptr.height == 0)
		return (error("Error: invalid value for screen height\n"));
	return (check_remaining_chars(line, "R"));
}

int			get_id_info(t_cub *scene, char *line)
{
	check_duplicates(scene, line);
	if (*line == 'R')
		return (set_screen_res(line, scene));
	else if (*line == 'F')
	{
		scene->type_id.f = 1;
		scene->rgb_ptr = &scene->floor;
		return (get_rgb_colour(scene, line, "F"));
	}
	else if (*line == 'C' && scene->id_ptr.c == 0)
	{
		scene->type_id.c = 1;
		scene->rgb_ptr = &scene->ceiling;
		return (get_rgb_colour(scene, line, "C"));
	}
	else if (ft_strncmp(line, "NO", 2) == 0 ||
	ft_strncmp(line, "SO", 2) == 0 ||
	ft_strncmp(line, "WE", 2) == 0 ||
	ft_strncmp(line, "EA", 2) == 0 ||
	ft_strncmp(line, "S", 1) == 0)
		return (set_tex_path(scene, line));
	return (error("Invalid type id\n"));
}
