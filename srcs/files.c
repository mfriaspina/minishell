/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:24:42 by mfrias            #+#    #+#             */
/*   Updated: 2019/07/03 15:38:09 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*ft_nopath(char *path)
{
	char	*new;
	int		i;
	int		j;

	new = path;
	i = -1;
	while (new[++i])
		if (new[i] == '/')
			j = i;
	return (&new[j + 1]);
}

static t_files	*ft_new_files(char *path, struct stat sb)
{
	t_files			*new;
	struct passwd	*pwd;
	struct group	*grp;

	pwd = getpwuid(sb.st_uid);
	grp = getgrgid(sb.st_gid);
	new = (t_files *)ft_memalloc(sizeof(t_files));
	new->sb = sb;
	new->name = path;
	new->nopath = ft_nopath(path);
	new->links = sb.st_nlink;
	new->size = sb.st_size;
	new->blocks = sb.st_blocks;
	new->id = pwd->pw_name;
	new->gid = grp->gr_name;
	new->time = sb.st_mtime;
	new->next = NULL;
	return (new);
}

static void		ft_add_files(t_files **alst, t_files *new)
{
	new->next = *alst;
	*alst = new;
}

void			get_files(t_options op, const char *str, t_files **list)
{
	DIR				*dir;
	struct dirent	*dent;
	struct stat		sb;
	char			*new;

	if (str[0] == '-')
		return ;
	dir = opendir(str);
	if (dir != NULL)
		while ((dent = readdir(dir)) != NULL)
		{
			new = ft_strnew(ft_strlen(str) + ft_strlen(dent->d_name) + 2);
			ft_strcpy(new, str);
			ft_strcat(new, "/");
			ft_strcat(new, dent->d_name);
			if (lstat(new, &sb) == 0)
			{
				if (op.dot || dent->d_name[0] != '.')
					ft_add_files(list, ft_new_files(new, sb));
				else
					ft_strdel(&new);
			}
		}
	closedir(dir);
}

void			recursive(t_options op, t_files *list)
{
	t_files *new;

	while (list)
	{
		new = NULL;
		if (ft_strcmp(".", list->nopath) && ft_strcmp("..", list->nopath))
			if (list->sb.st_mode & S_IFDIR)
			{
				ft_putchar('\n');
				ft_putstr(list->name);
				ft_putendl(":");
				get_files(op, list->name, &new);
				sort(&new, op.sort);
				if (op.rev)
					reverse(&new);
				print(new, op);
				if (op.sub)
					recursive(op, new);
				free_files(new);
			}
		list = list->next;
	}
}
