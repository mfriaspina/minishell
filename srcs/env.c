/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 18:59:45 by mfrias            #+#    #+#             */
/*   Updated: 2019/11/22 15:29:15 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_line(char **line, char *new)
{
	int	j;

	j = -1;
	while (line[++j])
		free(line[j]);
	free(line);
	if (new)
		free(new);
}

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
	char	**line;

	if (argc <= 2)
		return ;
	new = ft_strjoin(argv[1], "=");
	new = ft_strcat(new, argv[2]);
	i = -1;
	while (envp[++i])
	{
		line = ft_strsplit(envp[i], '=');
		if (!ft_strcmp(line[0], argv[1]))
		{
			free(envp[i]);
			envp[i] = ft_strdup(new);
			free_line(line, new);
			return ;
		}
		free_line(line, NULL);
	}
	free(envp[i]);
	envp[i] = ft_strdup(new);
	envp[i + 1] = NULL;
	free(new);
}

void	ft_unsetenv(char **argv, char **envp)
{
	int		i;
	char	**line;

	i = -1;
	while (envp[++i])
	{
		line = ft_strsplit(envp[i], '=');
		if (!ft_strcmp(line[0], argv[1]))
		{
			free(envp[i]);
			while (envp[++i])
				envp[i - 1] = envp[i];
			i--;
			envp[i--] = NULL;
		}
		free_line(line, NULL);
	}
}

char	*ft_getenv(char **envp, char *var)
{
	int		i;
	char	**line;
	char	*ret;

	i = -1;
	ret = NULL;
	while (envp[++i])
	{
		line = ft_strsplit(envp[i], '=');
		if (!ft_strcmp(line[0], var))
			ret = ft_strdup(line[1]);
		free_line(line, NULL);
	}
	return (ret);
}
