/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 16:14:25 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/11/04 10:31:48 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Check for invalid characters after R/S/C/F/NO/SO/EA/WE
*/

int			check_remaining_chars(char *line, char *type)
{
	while (*line)
	{
		if (*line == SPACE)
			skip_space(&line);
		else
		{
			if (!ft_strncmp(type, "R", 1))
				return (error("Error: invalid character(s) after R\n"));
			else if (!ft_strncmp(type, "F", 1))
				return (error("Error: invalid character(s) after F\n"));
			else if (!ft_strncmp(type, "C", 1))
				return (error("Error: invalid character(s) after C\n"));
			else if (!ft_strncmp(type, "P", 1))
				return (error("Invalid character(s) after tex path\n"));
		}
	}
	return (SUCCESS);
}

/*
** Check for duplicate type id's
*/

int			check_duplicates(t_cub *scene, char *line)
{
	if ((*line == 'R' && scene->type_id.r == 1) ||
		(*line == 'F' && scene->type_id.f == 1) ||
		(*line == 'C' && scene->type_id.c == 1) ||
		((ft_strncmp(line, "NO", 2)) == 0 && scene->no_tex_path != NULL) ||
		((ft_strncmp(line, "SO", 2)) == 0 && scene->so_tex_path != NULL) ||
		((ft_strncmp(line, "WE", 2)) == 0 && scene->we_tex_path != NULL) ||
		((ft_strncmp(line, "EA", 2)) == 0 && scene->ea_tex_path != NULL) ||
		((ft_strncmp(line, "S ", 2)) == 0 && scene->sprite_tex_path != NULL))
		return (error("Error: duplicate type id(s) detected\n"));
	else if (scene->id_count != 8)
		scene->id_count++;
	return (SUCCESS);
}

/*
** Validity check before parsing the map
*/

static int	check_line(t_cub *scene, char *line)
{
	if (scene->start_map == 0)
		check_duplicates(scene, line);
	else if (*line == '\0' && scene->start_map == 1 && scene->ret > 0)
	{
		scene->end_map = 1;
		return (SUCCESS);
	}
	else if (*line != '\0' && scene->end_map == 1)
		return (error("Error: invalid character(s) after map\n"));
	return (SUCCESS);
}

int			parse_scene(t_cub *scene, char *line)
{
	if (*line == '\0' && scene->start_map == 0)
		return (SUCCESS);
	else if (scene->id_count == 8)
	{
		if (check_line(scene, line) == SUCCESS)
			return (get_map(scene, line));
	}
	else
	{
		skip_space(&line);
		if ((ft_strchr("RSFC", *line) && *(line + 1) == SPACE) ||
			ft_strncmp(line, "NO ", 3) == 0 ||
			ft_strncmp(line, "SO ", 3) == 0 ||
			ft_strncmp(line, "WE ", 3) == 0 ||
			ft_strncmp(line, "EA ", 3) == 0)
			return (get_id_info(scene, line));
		else if (!(ft_strchr("012", *line)))
			return (error("Error: invalid type id detected\n"));
		else
			return (error("Error: missing type id(s)\n"));
	}
	return (SUCCESS);
}
