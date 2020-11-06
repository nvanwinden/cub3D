/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_bmp.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 10:39:02 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/11/06 17:11:32 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Write pixels to int array
*/

static int	get_pixel_array(t_game *game, int imagesize)
{
	int		i;

	i = 0;
	game->bmp.y = game->height - 1;
	game->bmp.pix_array = ft_calloc(imagesize, sizeof(int));
	if (game->bmp.pix_array == NULL)
	{
		close(game->bmp.fd);
		return (error("Malloc error for game->bmp.pix_array\n"));
	}
	while (game->bmp.y >= 0)
	{
		game->bmp.x = 0;
		while (game->bmp.x < game->width)
		{
			game->bmp.dest = game->mlx.addr + (game->bmp.y *
			game->mlx.line_length + game->bmp.x *
			(game->mlx.bits_per_pixel / 8));
			game->bmp.pix_array[i] = *(unsigned int*)game->bmp.dest;
			i++;
			game->bmp.x++;
		}
		game->bmp.y--;
	}
	return (SUCCESS);
}

/*
** Write int bytes to char array
*/

static void	int_to_dest(int num, char *dest)
{
	dest[0] = (char)(num);
	dest[1] = (char)(num >> 8);
	dest[2] = (char)(num >> 16);
	dest[3] = (char)(num >> 24);
}

/*
** Initialize bitmap header and write header to file
*/

static int	init_bmp_header(t_game *game)
{
	int		ret;
	char	header_buf[54];

	ft_bzero(&header_buf, 54);
	header_buf[0] = 'B';
	header_buf[1] = 'M';
	int_to_dest(game->bmp.file_size, &(header_buf[2]));
	int_to_dest(54, &(header_buf[10]));
	int_to_dest(40, &(header_buf[14]));
	int_to_dest(game->width, &(header_buf[18]));
	int_to_dest(game->height, &(header_buf[22]));
	int_to_dest(1, &(header_buf[26]));
	int_to_dest(game->mlx.bits_per_pixel, &(header_buf[28]));
	int_to_dest(game->bmp.file_size - 54, &(header_buf[34]));
	ret = write(game->bmp.fd, &header_buf, 54);
	if (ret == ERROR)
	{
		close(game->bmp.fd);
		return (error("Error: could not write header to file\n"));
	}
	return (SUCCESS);
}

int			save_bmp(t_game *game)
{
	int	ret;

	game->bmp.file_size = game->height * game->width *
	(game->mlx.bits_per_pixel / 8) + 54;
	game->bmp.fd = open("image.bmp", O_RDWR | O_CREAT, 0644);
	if (game->bmp.fd == ERROR)
		return (error("Error: image.bmp could not be opened\n"));
	init_bmp_header(game);
	get_pixel_array(game, game->bmp.file_size - 54);
	ret = write(game->bmp.fd, game->bmp.pix_array, game->bmp.file_size - 54);
	if (ret == ERROR)
	{
		free(game->bmp.pix_array);
		close(game->bmp.fd);
		return (error("Error: could not write pixel array to bitmap\n"));
	}
	free(game->bmp.pix_array);
	close(game->bmp.fd);
	return (SUCCESS);
}
