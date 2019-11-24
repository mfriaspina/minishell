/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:16:14 by mfrias            #+#    #+#             */
/*   Updated: 2019/11/23 17:28:25 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <limits.h>

int				echo(int argc, char **argv, char **envp);
int				pwd(void);
int				cd(int argc, char **argv, char **envp);

void			free_line(char **line, char *new);
char			*ft_getenv(char **envp, char *var);
void			env(int argc, char **argv, char **envp);
void			ft_setenv(int argc, char **argv, char **envp);
void			ft_unsetenv(char **argv, char **envp);

int				find_process(char *name, char **argv, char **envp);
void			start_envp(char **envp, char **argv);
void			new_process(char *name, char **argv, char **envp);

char			**get_command(char *s);
void			do_command(int *i, char *line, char **envp);

#endif
