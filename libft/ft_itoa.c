/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:20:23 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/05/14 17:55:33 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fillstr(char *s, int n, int i)
{
	if (n == -2147483648)
	{
		s[0] = '-';
		s[1] = 2 + '0';
		n = 147483648;
	}
	if (n < 0)
	{
		s[0] = '-';
		n = n * -1;
	}
	if (n >= 10)
		ft_fillstr(s, n / 10, i - 1);
	s[i] = n % 10 + '0';
	return (s);
}

char		*ft_itoa(int n)
{
	int		i;
	char	*str;
	int		count;

	i = 0;
	if (n <= 0)
		i++;
	count = n;
	while (count != 0)
	{
		count = count / 10;
		i++;
	}
	str = ft_calloc(i + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_fillstr(str, n, i - 1);
	str[i] = '\0';
	return (str);
}
