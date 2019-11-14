/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:18:49 by mfrias            #+#    #+#             */
/*   Updated: 2019/07/03 15:55:09 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <dirent.h>
# include <time.h>
# include <grp.h>

typedef struct		s_options
{
	char			yes;
	char			lng;
	char			sub;
	char			dot;
	char			rev;
	char			sort;
	char			mult;
	char			color;
}					t_options;

typedef struct		s_files
{
	struct stat		sb;
	char			*name;
	char			*nopath;
	int				links;
	int				size;
	int				blocks;
	char			*id;
	char			*gid;
	long			time;
	struct s_files	*next;
}					t_files;

int					ls(int argc, char **argv);

void				print(t_files *list, t_options op);

void				get_files(t_options op, const char *str, t_files **list);
void				recursive(t_options op, t_files *list);

void				sort(t_files **list, char sortby);
void				reverse(t_files **list);

int					total(t_files *list);
int					hardlinks(t_files *list);
void				print_long(t_options op, t_files *list, int max,
					int maxlink);

void				free_files(t_files *head);
void				minimum(int min, int num);
void				precision(int precision, char *size);
void				print_options(t_options op, t_files *list);

#endif
