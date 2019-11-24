/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:14:39 by mfrias            #+#    #+#             */
/*   Updated: 2019/11/23 20:21:40 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		echo(int argc, char **argv, char **envp)
{
	int		i;
	char	*msg;

	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '$')
			msg = ft_getenv(envp, &argv[i][1]);
		else
			msg = ft_strdup(argv[i]);
		if (!msg)
			ft_printf("%s: unknown environment variable", &argv[i][1]);
		else
		{
			ft_putstr(msg);
			free(msg);
			if (i + 1 != argc)
				ft_putchar(' ');
		}
	}
	ft_putchar('\n');
	return (1);
}

int		pwd(void)
{
	char *path;

	path = getcwd(NULL, PATH_MAX);
	ft_putendl(path);
	free(path);
	return (1);
}

void	changeoldpwd(char **envp)
{
	char	*new;
	char	*path;
	char	**line;
	int		i;

	path = getcwd(NULL, PATH_MAX);
	new = ft_strjoin("OLDPWD=", path);
	free(path);
	i = -1;
	while (envp[++i])
	{
		line = ft_strsplit(envp[i], '=');
		if (!ft_strcmp(line[0], "OLDPWD"))
		{
			free(envp[i]);
			envp[i] = ft_strdup(new);
			free_line(line, new);
			return ;
		}
		free_line(line, NULL);
	}
}

int		cd(int argc, char **argv, char **envp)
{
	char *path;

	if (argc == 1)
		path = ft_getenv(envp, "HOME");
	else
	{
		if (!ft_strcmp("-", argv[1]))
		{
			path = ft_getenv(envp, "OLDPWD");
			ft_printf("%s\n", path);
		}
		else if (argv[1][0] == '~')
			path = ft_strcat(ft_getenv(envp, "HOME"), &argv[1][1]);
		else
			path = ft_strdup(argv[1]);
	}
	changeoldpwd(envp);
	chdir(path);
	free(path);
	return (1);
}
