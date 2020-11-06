/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_texture.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 09:10:45 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/11/04 10:07:47 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*get_path(t_cub *scene, char *tex_path, int i)
{
	if (i == 0)
		tex_path = scene->no_tex_path;
	else if (i == 1)
		tex_path = scene->so_tex_path;
	else if (i == 2)
		tex_path = scene->we_tex_path;
	else if (i == 3)
		tex_path = scene->ea_tex_path;
	else if (i == 4)
		tex_path = scene->sprite_tex_path;
	return (tex_path);
}

int			set_texture(t_game *game, t_cub *scene)
{
	int		i;
	char	*tex_path;

	i = 0;
	while (i < 5)
	{
		tex_path = get_path(scene, tex_path, i);
		game->tex[i].img = mlx_xpm_file_to_image(game->mlx.mlx, tex_path,
		&game->tex[i].width, &game->tex[i].height);
		if (game->tex[i].img == NULL)
			return (error("Could not create an image out of .xpm file\n"));
		game->tex[i].addr = mlx_get_data_addr(game->tex[i].img,
		&game->tex[i].bits_per_pixel, &game->tex[i].line_length,
		&game->tex[i].endian);
		i++;
	}
	return (SUCCESS);
}
