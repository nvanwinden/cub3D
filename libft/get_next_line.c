/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/26 10:57:35 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/09/21 11:24:09 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	read_line(char *str, char *buff, char **line)
{
	int i;
	int y;

	i = 0;
	y = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	*line = ft_substr(str, 0, i);
	if (*line == NULL)
	{
		free(str);
		return (-1);
	}
	while (buff[y] != '\n' && buff[y] != '\0')
		y++;
	if (buff[y] == '\n')
	{
		ft_memmove(buff, buff + y + 1, ft_strlen(buff) - y);
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

static char	*get_line(char *str, char *buff)
{
	char	*s;

	s = ft_strjoin(str, buff);
	if (s == NULL)
	{
		free(str);
		return (NULL);
	}
	free(str);
	return (s);
}

int			get_next_line(int fd, char **line)
{
	static char	buff[OPEN_MAX][BUFFER_SIZE + 1];
	char		*str;
	ssize_t		ret;

	ret = 1;
	if (fd < 0 || line == NULL || BUFFER_SIZE == 0)
		return (-1);
	str = ft_strdup(buff[fd]);
	if (str == NULL)
		return (-1);
	while (ret > 0 && ft_strchr(buff[fd], '\n') == NULL)
	{
		ret = read(fd, buff[fd], BUFFER_SIZE);
		if (ret == -1)
		{
			free(str);
			return (-1);
		}
		buff[fd][ret] = '\0';
		str = get_line(str, buff[fd]);
		if (str == NULL)
			return (-1);
	}
	return (read_line(str, buff[fd], line));
}
