/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:30:32 by mfrias            #+#    #+#             */
/*   Updated: 2019/11/23 19:06:12 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_wordcount(char const *s)
{
	int	num;
	int	i;
	int	size;

	num = 0;
	i = 0;
	while (s[i] != '\0')
	{
		size = 0;
		if (s[i] == '"')
			while (s[++i] != '"' && s[i])
				size = 1;
		else
			while (s[++i] != ' ' && s[i])
				size = 1;
		if (s[i] == ' ' && s[i + 1] && s[i + 2])
			i++;
		if (size)
			num++;
	}
	return (num);
}

int			loop(size_t i, char *s, size_t j, char **arr)
{
	if (*s != '"')
	{
		while (s[i] != ' ' && s[i])
			i++;
		if ((arr[j] = ft_strsub(s, 0, i)) == NULL)
			return (0);
	}
	else
	{
		s++;
		while (s[i] != '"' && s[i])
			i++;
		if ((arr[j] = ft_strsub(s, 0, i)) == NULL)
			return (0);
	}
	return (i);
}

char		**get_command(char *s)
{
	size_t	size;
	char	**arr;
	size_t	j;
	size_t	i;

	j = 0;
	if (!s)
		return (NULL);
	size = ft_wordcount(s);
	if (!(arr = (char **)ft_memalloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (0 < size)
	{
		while (*s == ' ' && *s)
			s++;
		if ((i = loop(0, s, j, arr)) == 0)
			return (NULL);
		j++;
		size--;
		s += i;
	}
	return (arr);
}
