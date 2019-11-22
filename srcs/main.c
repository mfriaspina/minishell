/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:21:43 by mfrias            #+#    #+#             */
/*   Updated: 2019/11/21 22:25:43 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	commands(char **com, int i, char **envp)
{
	if (!i)
		return ;
	else if (com[0][0] == '.' || com[0][0] == '/')
		new_process(com[0], com, envp);
	else if (!ft_strcmp(com[0], "echo"))
		echo(i, com, envp);
	else if (!ft_strcmp(com[0], "pwd"))
		pwd();
	else if (!ft_strcmp(com[0], "cd"))
		cd(i, com, envp);
	else if (!ft_strcmp(com[0], "env"))
		env(i, &com[0], envp);
	else if (!ft_strcmp(com[0], "setenv"))
		ft_setenv(i, &com[0], envp);
	else if (!ft_strcmp(com[0], "unsetenv"))
		ft_unsetenv(&com[0], envp);
	else
		find_process(com[0], com, envp);
}

void	do_command(int *i, char *line, char **envp)
{
	int		j;
	char	*new;
	char	**command;

	if (line)
	{
		new = ft_strtrim(line);
		command = get_command(new);
		free(new);
		while (command[*i])
			(*i)++;
		commands(command, *i, envp);
		j = -1;
		while (command[++j])
			free(command[j]);
		free(command);
	}
}

int		main(int argc, char **argv, char **envp)
{
	int		i;
	char	*line;

	if (argc == 1)
		start_envp(envp, argv);
	while (1)
	{
		ft_printf("$>");
		get_next_line(1, &line);
		if (line && !ft_strcmp(line, "exit"))
		{
			free(line);
			exit(0);
		}
		i = 0;
		do_command(&i, line, envp);
		free(line);
	}
	return (0);
}
