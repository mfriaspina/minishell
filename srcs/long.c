/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:21:04 by mfrias            #+#    #+#             */
/*   Updated: 2019/07/03 15:55:28 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					total(t_files *list)
{
	int	tot;
	int	len;
	int	max;
	int	size;

	tot = 0;
	max = 0;
	while (list != NULL)
	{
		tot += list->blocks;
		size = list->size;
		len = 0;
		while (size)
		{
			size /= 10;
			len++;
		}
		if (len > max)
			max = len;
		list = list->next;
	}
	ft_putnbr_endl(tot);
	return (max);
}

int					hardlinks(t_files *list)
{
	int max;
	int len;
	int size;

	max = 0;
	while (list != NULL)
	{
		size = list->links;
		len = 0;
		while (size)
		{
			size /= 10;
			len++;
		}
		if (len > max)
			max = len;
		list = list->next;
	}
	return (max);
}

static char			entry_type(mode_t perm)
{
	if (perm & S_IFIFO)
		return ('p');
	if (perm & S_IFCHR)
		return ('c');
	if (perm & S_IFDIR)
		return ('d');
	if (perm & S_IFBLK)
		return ('b');
	if (perm & S_IFREG)
		return ('-');
	if (perm & S_IFLNK)
		return ('l');
	if (perm & S_IFSOCK)
		return ('s');
	return ('-');
}

static void			permissions(struct stat sb)
{
	mode_t		perm;
	char		modeval[13];

	perm = sb.st_mode;
	modeval[0] = entry_type(perm);
	modeval[1] = (perm & S_IRUSR) ? 'r' : '-';
	modeval[2] = (perm & S_IWUSR) ? 'w' : '-';
	modeval[3] = (perm & S_IXUSR) ? 'x' : '-';
	modeval[4] = (perm & S_IRGRP) ? 'r' : '-';
	modeval[5] = (perm & S_IWGRP) ? 'w' : '-';
	modeval[6] = (perm & S_IXGRP) ? 'x' : '-';
	modeval[7] = (perm & S_IROTH) ? 'r' : '-';
	modeval[8] = (perm & S_IWOTH) ? 'w' : '-';
	modeval[9] = (perm & S_IXOTH) ? 'x' : '-';
	modeval[10] = ' ';
	modeval[11] = ' ';
	modeval[12] = '\0';
	ft_putstr(modeval);
}

void				print_long(t_options op, t_files *list, int max,
								int maxlink)
{
	permissions(list->sb);
	minimum(maxlink, list->links);
	ft_putnbr(list->links);
	ft_putstr(" ");
	ft_putstr(list->id);
	ft_putstr("  ");
	ft_putstr(list->gid);
	ft_putstr("  ");
	minimum(max, list->size);
	ft_putnbr(list->size);
	ft_putstr(" ");
	precision(12, &(ctime(&list->time)[4]));
	ft_putstr(" ");
	print_options(op, list);
}
