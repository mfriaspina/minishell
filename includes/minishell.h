/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:16:14 by mfrias            #+#    #+#             */
/*   Updated: 2019/11/15 21:27:49 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_ls.h"
# include "../libft/libft.h"

int				echo(int argc, char **argv, char **envp);
int				pwd(void);
int				cd(int argc, char **argv, char **envp);

char			*ft_getenv(char **envp, char *var);
void			env(int argc, char **argv, char **envp);
void			ft_setenv(int argc, char **argv, char **envp);
void			ft_unsetenv(char **argv, char **envp);

void			new_process(char *name, char **argv, char **envp);

#endif
