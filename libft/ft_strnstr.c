/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 16:24:56 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/04/17 16:28:24 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str;
	char	*sub;
	size_t	i;
	size_t	j;

	str = (char*)haystack;
	sub = (char*)needle;
	i = 0;
	if (sub[i] == '\0')
		return (str);
	while (str[i] && i < len)
	{
		j = 0;
		if (str[i] == sub[j])
		{
			while (str[i + j] == sub[j] && i + j < len)
			{
				j++;
				if (sub[j] == '\0')
					return (&str[i]);
			}
		}
		i++;
	}
	return (NULL);
}
