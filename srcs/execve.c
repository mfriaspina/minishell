/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:50:39 by mfrias            #+#    #+#             */
/*   Updated: 2019/11/21 19:40:12 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_process(char *name, char **argv, char **envp)
{
	char	*temp;
	char	**paths;
	char	*path;
	int		i;

	temp = ft_getenv(envp, "PATH");
	paths = ft_strsplit(temp, ':');
	free(temp);
	path = NULL;
	i = -1;
	while (!path && paths[++i])
	{
		path = ft_strcat(paths[i], "/");
		path = ft_strcat(path, name);
		if (access(path, F_OK | X_OK) != 0)
			path = NULL;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	execve(path, argv, envp);
	ft_printf("%s: command not found\n", name);
}

void	start_envp(char **envp, char **argv)
{
	int		i;
	char	*new;

	i = -1;
	if (argv[1])
		return ;
	while (envp[++i])
	{
		new = ft_strdup(envp[i]);
		envp[i] = new;
	}
}

void	new_process(char *name, char **argv, char **envp)
{
	pid_t	pid;

	if (!name)
		return ;
	pid = fork();
	if (pid == 0)
		execve(name, argv, envp);
	else
		wait(NULL);
}
