/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 17:07:15 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/11/04 13:03:27 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		get_digit(char **line)
{
	int ret;

	ret = 0;
	while (ft_isdigit(**line))
	{
		ret = (ret * 10) + (**line - '0');
		(*line)++;
	}
	if (ret < 0)
		ret = 2147483647;
	return (ret);
}

void	skip_space(char **line)
{
	while (**line == SPACE)
		(*line)++;
}
