/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:14:39 by mfrias            #+#    #+#             */
/*   Updated: 2019/11/22 16:10:52 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(int argc, char **argv, char **envp)
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
		ft_putstr(msg);
		free(msg);
		if (i + 1 != argc)
			ft_putchar(' ');
	}
	ft_putchar('\n');
	return (1);
}

int	pwd(void)
{
	char *path;

	path = getcwd(NULL, 1);
	ft_putendl(path);
	free(path);
	return (1);
}

int	cd(int argc, char **argv, char **envp)
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
	chdir(path);
	free(path);
	return (1);
}
