/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:13:25 by mfrias            #+#    #+#             */
/*   Updated: 2019/06/11 18:47:43 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		typef(va_list ap, t_flags *flag, double val)
{
	char	*n;

	flag->precision = flag->precision == -1 ? 6 : flag->precision;
	if (flag->length == 5)
		val = va_arg(ap, long double);
	else
		val = va_arg(ap, double);
	n = ft_ftoa(val, flag->precision);
	while ((int)ft_strlen(n) < flag->precision)
		n = free_strjoin("0", n, 1);
	if (flag->zero && val < 0)
		*n = '0';
	while ((int)ft_strlen(n) < flag->width)
		n = !flag->left ? free_strjoin(" ", n, 1) : free_strjoin(n, " ", 0);
	n = flag->zero ? ft_replace(n, '0', ' ') : n;
	if (flag->prepend && val >= 0)
		n = flag->prepend == '+' ?
			free_strjoin("+", n, 1) : free_strjoin(" ", n, 1);
	if (flag->zero && val < 0)
		*n = '-';
	if (flag->hash)
		n = free_strjoin(n, ".", 0);
	return (clean(n));
}

int		typep(va_list ap, t_flags *flag)
{
	int		i;
	char	*n;

	n = ft_hexa((size_t)va_arg(ap, void *));
	if (!flag->precision && *n == '0')
	{
		ft_putstr("0x");
		return (2);
	}
	while (flag->precision > (int)ft_strlen(n))
		n = ft_strjoin("0", n);
	n = ft_strjoin("0x", n);
	i = ft_strlen(n) - 1;
	i = width(flag, i, n);
	return (i);
}

int		typec(va_list ap, t_flags *flag)
{
	char	c;
	int		i;

	i = 0;
	c = va_arg(ap, int);
	if (flag->left)
		ft_putchar(c);
	while (++i < flag->width)
	{
		if (!flag->zero)
			ft_putchar(' ');
		else
			ft_putchar('0');
	}
	if (!flag->left)
		ft_putchar(c);
	return (i);
}

int		typepercent(t_flags *flag)
{
	int		i;

	i = 0;
	i = width(flag, i, "%");
	return (i);
}

int		typest(va_list ap, t_flags *flag)
{
	char	*n;
	int		i;

	n = va_arg(ap, char *);
	if (flag->zero && n == NULL)
		n = "0";
	if (n == NULL)
	{
		ft_putstr("(null)");
		return (6);
	}
	if (flag->precision != -1)
		n = ft_strsub(n, 0, flag->precision);
	i = ft_strlen(n) - 1;
	i = width(flag, i, n);
	return (i);
}
