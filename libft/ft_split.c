/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/22 15:01:02 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/05/14 17:09:16 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(char const *s, char c)
{
	int i;
	int count;
	int flag;

	i = 0;
	count = 0;
	flag = 0;
	if (s == 0)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			flag = 0;
		else if (flag == 0)
		{
			flag = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static char	**ft_free(char **str, int j)
{
	while (j > 0)
	{
		j--;
		free(str[j]);
	}
	free(str);
	return (NULL);
}

static char	**ft_memfill(char *s, char **str, char c, int j)
{
	size_t	i;
	size_t	start;
	size_t	k;

	i = 0;
	while ((ft_strlen(s)) > i)
	{
		k = 0;
		while (s[i] == c)
			i++;
		if (s[i] != c)
			start = i;
		while (s[i] != c && s[i])
		{
			i++;
			k++;
		}
		if (start == i)
			return (str);
		str[j] = ft_substr(s, start, k);
		if (str[j] == NULL)
			return (ft_free(str, j));
		j++;
	}
	return (str);
}

char		**ft_split(char const *s, char c)
{
	char	**str;
	int		words;
	int		j;

	j = 0;
	if (s == NULL)
		return (NULL);
	words = ft_wordcount(s, c);
	str = (char**)ft_calloc((words + 1), sizeof(char*));
	if (str == NULL)
		return (NULL);
	str = ft_memfill((char*)s, str, c, j);
	if (str == NULL)
		return (NULL);
	str[words] = NULL;
	return (str);
}
