/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 13:49:38 by mfrias            #+#    #+#             */
/*   Updated: 2019/06/11 18:47:13 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		clean(char *str)
{
	int val;

	ft_putstr(str);
	val = ft_strlen(str);
	if (ft_strcmp("0", str) && ft_strcmp("", str))
		free(str);
	return (val);
}

char	*free_strjoin(char *one, char *two, int i)
{
	char	*temp;

	temp = ft_strjoin(one, two);
	if (*one && *two)
	{
		if (!i)
			free(one);
		else
			free(two);
	}
	return (temp);
}

int		width(t_flags *flag, int i, char *s)
{
	if (flag->left)
		ft_putstr(s);
	while (++i < flag->width)
	{
		if (!flag->zero)
			ft_putchar(' ');
		else
			ft_putchar('0');
	}
	if (!flag->left)
		ft_putstr(s);
	return (i);
}
