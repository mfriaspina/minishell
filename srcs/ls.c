/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:19:54 by mfrias            #+#    #+#             */
/*   Updated: 2019/07/04 13:02:12 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_options	options(char *str)
{
	t_options	op;

	op = (t_options) {0, 0, 0, 0, 0, 0, 0, 0};
	if (str[0] == '-')
	{
		op.yes = 1;
		op.lng = ft_strchr(str, 'l') == NULL ? 0 : 1;
		op.sub = ft_strchr(str, 'R') == NULL ? 0 : 1;
		op.dot = ft_strchr(str, 'a') == NULL ? 0 : 1;
		op.rev = ft_strchr(str, 'r') == NULL ? 0 : 1;
		op.sort = ft_strchr(str, 't') == NULL ? 0 : 1;
		op.color = ft_strchr(str, 'G') == NULL ? 0 : 1;
	}
	return (op);
}

void				print(t_files *list, t_options op)
{
	int		max;
	int		maxlink;

	if (op.lng)
	{
		ft_putstr("total ");
		max = total(list);
		maxlink = hardlinks(list);
	}
	while (list != NULL)
	{
		if (op.lng)
			print_long(op, list, max, maxlink);
		else
			print_options(op, list);
		list = list->next;
	}
}

static void			is_dir(t_options op, char *name, char **dir, int num)
{
	t_files *new;

	new = NULL;
	if (num == 2)
	{
		ft_putstr(dir[0]);
		ft_putendl(":");
	}
	get_files(op, name, &new);
	sort(&new, op.sort);
	if (op.rev)
		reverse(&new);
	print(new, op);
	if (dir[1])
		ft_putchar('\n');
	free_files(new);
}

static void			multiple(t_options op, t_files *list, char **dir, int num)
{
	int		i;

	ft_sort(dir);
	while (list)
	{
		i = 0;
		while (dir[++i])
		{
			if (!ft_strcmp(dir[i], list->nopath) && list->sb.st_mode & S_IFDIR)
				is_dir(op, list->name, &dir[i], num);
			else if (!ft_strcmp(dir[i], list->nopath))
			{
				ft_putendl(dir[i]);
				if (dir[i + 1])
					ft_putchar('\n');
			}
		}
		list = list->next;
	}
}

int					ls(int argc, char **argv)
{
	t_options	op;
	t_files		*list;

	list = NULL;
	op = (t_options) {0, 0, 0, 0, 0, 0, 0, 0};
	if (argc > 1 && argv[1][0] == '-')
		op = options(argv[1]);
	if ((argc == 2 && argv[1][0] != '-') || argc > 2)
		op.mult = argc == 2 || (argc == 3 && argv[1][0] == '-') ? 1 : 2;
	get_files(op, ".", &list);
	sort(&list, op.sort);
	if (op.rev)
		reverse(&list);
	if (op.mult == 0)
		print(list, op);
	else
		multiple(op, list, &argv[0], op.mult);
	if (op.sub)
		recursive(op, list);
	free_files(list);
	return (1);
}
