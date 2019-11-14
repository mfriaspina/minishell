/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:14:39 by mfrias            #+#    #+#             */
/*   Updated: 2019/11/13 18:57:36 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(int argc, char **argv)
{
	int i;

	i = 0;
	while (++i < argc)
	{
		ft_putstr(argv[i]);
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

	path = envp[0];
	path = getcwd(NULL, 1);
	if (argc == 3)
		chdir("");
	else if (argc == 2)
		chdir(argv[1]);
	free(path);
	return (1);
}
