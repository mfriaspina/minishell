/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:17:06 by mfrias            #+#    #+#             */
/*   Updated: 2019/05/14 15:21:03 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_new(char **list, char **line, int fd, int ret)
{
	char *temp;

	if (list[fd][ft_strsize(list[fd], '\n')] == '\n')
	{
		*line = ft_strsub(list[fd], 0, ft_strsize(list[fd], '\n'));
		temp = ft_strdup(list[fd] + 1 + ft_strsize(list[fd], '\n'));
		free(list[fd]);
		list[fd] = temp;
		if (!list[fd][0])
			ft_strdel(&list[fd]);
	}
	else if (!list[fd][ft_strsize(list[fd], '\n')])
	{
		if (ret == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(list[fd]);
		ft_strdel(&list[fd]);
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*list[255];
	char		str[BUFF_SIZE + 1];
	char		*temp;
	int			ret;

	if ((fd < 0 || line == NULL || read(fd, str, 0) < 0))
		return (-1);
	while ((ret = read(fd, str, BUFF_SIZE)) > 0)
	{
		str[ret] = '\0';
		if (!list[fd])
			list[fd] = ft_strnew(1);
		temp = ft_strjoin(list[fd], str);
		free(list[fd]);
		list[fd] = temp;
		if (ft_strchr(str, '\n'))
			break ;
	}
	if (ret == 0 && (!list[fd] || !list[fd][0]))
		return (0);
	return (ft_get_new(list, line, fd, ret));
}
