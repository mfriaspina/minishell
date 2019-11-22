/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:50:39 by mfrias            #+#    #+#             */
/*   Updated: 2019/11/21 22:24:24 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_stuff(char **paths, char *temp)
{
	int	i;

	i = -1;
	if (paths)
	{
		while (paths[++i])
			free(paths[i]);
		free(paths);
	}
	free(temp);
}

void	find_process(char *name, char **argv, char **envp)
{
	char	*temp;
	char	**paths;
	char	*path;
	int		i;

	temp = ft_getenv(envp, "PATH");
	paths = ft_strsplit(temp, ':');
	free(temp);
	temp = ft_strdup(name);
	path = NULL;
	i = -1;
	while (!path && paths && paths[++i])
	{
		path = ft_strcat(paths[i], "/");
		path = ft_strcat(path, temp);
		if (access(path, F_OK | X_OK) != 0)
			path = NULL;
	}
	if (path)
		new_process(path, argv, envp);
	else
		ft_printf("%s: command not found\n", temp);
	free_stuff(paths, temp);
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

	pid = fork();
	if (pid == 0)
		execve(name, argv, envp);
	else
		wait(NULL);
}
