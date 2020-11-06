/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/07 16:11:40 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/11/04 14:35:04 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Write error message to file descriptor 2 (STDERR)
*/

int			error(char *message)
{
	ft_putstr_fd(message, 2);
	exit(1);
}

/*
** Final validity check for .cub file
*/

static int	scene_check(t_cub *scene)
{
	if (scene->id_count == 0 && scene->start_map == 0)
		return (error("Error: file appears to be empty\n"));
	else if (scene->id_count != 8)
		return (error("Error: missing type id(s)\n"));
	else if (scene->start_map == 0)
		return (error("Error: no map detected\n"));
	return (SUCCESS);
}

/*
** Check if command line argument(s) are valid
*/

static int	input_check(int argc, char **argv, t_cub *scene)
{
	if (argc < 2 || argc > 3)
		return (error("Error: invalid amount of arguments\n"));
	else if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4))
		return (error("Error: scene file should have a .cub extension\n"));
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7))
			return (error("Error: try --save as second argument\n"));
		else
			scene->save_bmp = 1;
	}
	return (SUCCESS);
}

int			main(int argc, char **argv)
{
	t_cub		scene;

	ft_bzero(&scene, sizeof(t_cub));
	input_check(argc, argv, &scene);
	scene.fd = open(argv[1], O_RDWR);
	if (scene.fd == ERROR)
		return (error("Error: .cub file could not be openend\n"));
	else
		scene.fd_flag = 1;
	scene.ret = 1;
	while (scene.ret > 0)
	{
		scene.ret = get_next_line(scene.fd, &scene.line);
		if (scene.ret == ERROR)
			return (error("Error: .cub file could not been read\n"));
		parse_scene(&scene, scene.line);
		free(scene.line);
	}
	close(scene.fd);
	scene_check(&scene);
	start_game(&scene);
	exit(0);
}
