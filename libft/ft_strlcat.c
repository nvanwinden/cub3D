/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 21:30:58 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/05/20 14:14:23 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dst == NULL && dstsize == 0)
		return (ft_strlen(src));
	while (dst[i] && dstsize > i)
		i++;
	if (i + 1 < dstsize)
		ft_strlcpy(&dst[i], src, dstsize - i);
	return (i + ft_strlen(src));
}
