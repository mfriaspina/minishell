/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:50:39 by mfrias            #+#    #+#             */
/*   Updated: 2019/11/15 16:55:21 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_process(char *name, char **argv, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execve(name, argv, envp);
	else
		wait(NULL);
}
