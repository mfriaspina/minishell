/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:17:20 by mfrias            #+#    #+#             */
/*   Updated: 2019/06/11 18:47:59 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		colors(t_flags *flag, char *str)
{
	if (!ft_strncmp("{r}", str, 3))
		ft_putstr(RED);
	else if (!ft_strncmp("{g}", str, 3))
		ft_putstr(GRN);
	else if (!ft_strncmp("{y}", str, 3))
		ft_putstr(YEL);
	else if (!ft_strncmp("{b}", str, 3))
		ft_putstr(BLU);
	else if (!ft_strncmp("{m}", str, 3))
		ft_putstr(MAG);
	else if (!ft_strncmp("{c}", str, 3))
		ft_putstr(CYN);
	else if (!ft_strncmp("{w}", str, 3))
		ft_putstr(WHT);
	else if (!ft_strncmp("{e}", str, 3))
		ft_putstr(END);
	else
		return (invalid(flag, *str));
	flag->size += 2;
	return (3);
}

int		binary(va_list ap)
{
	char			*n;
	unsigned int	num;
	int				i;

	i = 0;
	num = va_arg(ap, unsigned int);
	n = ft_strnew(1);
	while (num > 0)
	{
		n[i] = num % 2 + '0';
		num = num / 2;
		i++;
	}
	n[i] = '\0';
	n = ft_strrev(n);
	ft_putstr(n);
	free(n);
	return (i - 1);
}

int		invalid(t_flags *flag, char c)
{
	int	i;

	i = 0;
	if (flag->left)
		ft_putchar(c);
	while (i < flag->width - 1)
	{
		if (!flag->zero)
			ft_putchar(' ');
		else
			ft_putchar('0');
		i++;
	}
	if (!flag->left)
		ft_putchar(c);
	return (i + 1);
}
