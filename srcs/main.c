/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:21:43 by mfrias            #+#    #+#             */
/*   Updated: 2019/11/13 19:25:10 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char **envp, char *var)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strstr(envp[i], var))
		{
			ft_putendl(envp[i]);
			return (envp[i]);
		}
	}
	return (NULL);
}

void	commands(char **com, int i, char **envp)
{
	if (!ft_strcmp(com[0], "ls"))
		ls(i, com);
	else if (!ft_strcmp(com[0], "echo"))
		echo(i, com);
	else if (!ft_strcmp(com[0], "pwd"))
		pwd();
	else if (!ft_strcmp(com[0], "cd"))
		cd(i, com, envp);
	else if (!ft_strcmp(com[0], "getenv"))
		ft_getenv(envp, com[1]);
	else if (!ft_strcmp(com[0], "env"))
		env(i, &com[0], envp);
	else
		ft_printf("%s: command not found\n", com[0]);
}

int		main(int argc, char **argv, char **envp)
{
	int		i;
	char	*line;
	char	**command;

	if (argc != 1)
		ft_printf(argv[1]);
	while (1)
	{
		ft_printf("$>");
		get_next_line(1, &line);
		if (!ft_strcmp(line, "exit"))
		{
			free(line);
			return (1);
		}
		if (line)
		{
			command = ft_strsplit(line, ' ');
			i = 0;
			while (command[i])
				i++;
			commands(command, i, envp);
			free(line);
		}
	}
	return (0);
}
