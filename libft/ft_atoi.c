/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/18 12:31:41 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/05/22 10:29:55 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int	n;
	int	flag;
	int	i;

	n = 0;
	flag = 1;
	i = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14) ||
	(str[i] == '+' && str[i + 1] >= '0' && str[i + 1] <= '9'))
		i++;
	if (str[i] == '-')
	{
		flag = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i] - '0');
		i++;
	}
	return (n * flag);
}
