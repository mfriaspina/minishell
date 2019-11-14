/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 13:29:46 by mfrias            #+#    #+#             */
/*   Updated: 2019/07/04 13:58:49 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		minimum(int min, int num)
{
	int size;

	size = 0;
	while (num)
	{
		size++;
		num /= 10;
	}
	while (size++ < min)
		ft_putchar(' ');
}

void		precision(int width, char *str)
{
	int i;

	i = -1;
	while (++i < width)
		ft_putchar(str[i]);
}

void		free_files(t_files *head)
{
	t_files *next;

	while (head)
	{
		next = head->next;
		ft_strdel(&(head->name));
		ft_memdel((void **)&head);
		head = next;
	}
}

static void	color(int mode)
{
	char	*col;

	col = END;
	if (mode & S_IFREG && !(mode & S_IEXEC))
		col = END;
	else if (mode & S_IEXEC)
	{
		if (mode & S_ISUID || mode & S_ISGID)
			col = mode & S_ISUID ? "\x1B[30;41m" : "\x1B[30;46m";
		else
			col = RED;
	}
	else if (mode & S_IFLNK)
		col = MAG;
	else if (mode & S_IFSOCK)
		col = GRN;
	ft_putstr(col);
}

void		print_options(t_options op, t_files *list)
{
	char	*col;
	int		mode;

	mode = list->sb.st_mode;
	if (op.color)
	{
		if (mode & S_IFIFO)
			ft_putstr(YEL);
		else if (mode & S_IFCHR)
			ft_putstr("\x1B[34;43m");
		else if (mode & S_IFDIR)
		{
			if (mode & S_IWGRP || mode & S_IWOTH)
				col = mode & S_ISVTX ? "\x1B[30;42m" : "\x1B[30;43m";
			else
				col = BLU;
			ft_putstr(col);
		}
		else if (mode & S_IFBLK)
			ft_putstr("\x1B[34;46m");
		else
			color(list->sb.st_mode);
	}
	ft_putstr(list->nopath);
	ft_putendl(END);
}
