/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 18:59:45 by mfrias            #+#    #+#             */
/*   Updated: 2019/11/19 12:42:15 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(int argc, char **argv, char **envp)
{
	int	i;

	i = -1;
	if (argc == 1)
	{
		while (envp[++i])
			ft_putendl(envp[i]);
		return ;
	}
	if (argv[0][0] == '-')
		ft_printf(argv[0]);
}

void	ft_setenv(int argc, char **argv, char **envp)
{
	int		i;
	char	*new;

	i = 0;
	while (envp[i])
		i++;
	if (argc == 2)
		envp[i] = ft_strdup(argv[1]);
	else
	{
		new = ft_strcat(argv[1], "=");
		envp[i] = ft_strdup(ft_strcat(new, argv[2]));
	}
	envp[i + 1] = NULL;
}

void	ft_unsetenv(char **argv, char **envp)
{
	int		i;
	int		j;
	char	**line;

	i = -1;
	while (envp[++i])
	{
		line = ft_strsplit(envp[i], '=');
		if (!ft_strcmp(line[0], argv[1]))
		{
			free(envp[i]);
			envp[i] = NULL;
		}
		j = -1;
		while (line[++j])
			free(line[j]);
		free(line);
	}
}

char	*ft_getenv(char **envp, char *var)
{
	int		i;
	int		j;
	char	**line;
	char	*ret;

	i = -1;
	ret = NULL;
	while (envp[++i])
	{
		line = ft_strsplit(envp[i], '=');
		if (!ft_strcmp(line[0], var))
			ret = ft_strdup(line[1]);
		j = -1;
		while (line[++j])
			free(line[j]);
		free(line);
	}
	return (ret);
}
