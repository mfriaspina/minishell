/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:55:00 by mfrias            #+#    #+#             */
/*   Updated: 2019/06/11 18:47:33 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	types(char *c, va_list ap, t_flags *flag)
{
	flag->width = ft_abs(flag->width);
	if (*c == '%')
		return (typepercent(flag));
	else if (*c == 'd' || *c == 'i' || *c == 'D')
		return (typed(ap, flag, 0));
	else if (*c == 'u' || *c == 'U')
		return (typeu(ap, flag, 0));
	else if (*c == 'o' || *c == 'O')
		return (typeo(ap, flag, 0));
	else if (*c == 'x' || *c == 'X')
		return (typex(ap, flag, 0, *c));
	else if (*c == 's')
		return (typest(ap, flag));
	else if (*c == 'c')
		return (typec(ap, flag));
	else if (*c == 'p')
		return (typep(ap, flag));
	else if (*c == 'f')
		return (typef(ap, flag, 0.0));
	else if (*c == '{')
		return (colors(flag, c));
	else if (*c == 'b')
		return (binary(ap));
	return (invalid(flag, *c));
}

static int	more(char *format, t_flags *flag, va_list ap)
{
	if (*format == '.')
	{
		if (!ft_isdigit(*(format + 1)))
		{
			flag->precision = format[1] == '*' ? (va_arg(ap, int)) : 0;
			if (*(format + 1) == '*')
				return (2);
			return (1);
		}
		flag->precision = ft_atoi(format + 1);
		return (ft_strlen(ft_itoa(flag->precision)) + 1);
	}
	else if (ft_isdigit(*format))
	{
		flag->width = ft_atoi(format);
		return (ft_strlen(ft_itoa(flag->width)));
	}
	else if (*format == '*')
		flag->width = va_arg(ap, int);
	else
	{
		*format != '\0' ? flag->size-- : flag->size;
		return (0);
	}
	return (1);
}

static int	flags(char *format, t_flags *flag, va_list ap)
{
	if (*format == '-')
		flag->left = 1;
	else if (*format == '0')
		flag->zero = 1;
	else if (*format == '#')
		flag->hash = 1;
	else if (*format == '+')
		flag->prepend = '+';
	else if (*format == ' ')
		flag->prepend = flag->prepend != '+' ? ' ' : '+';
	else if (*format == 'L')
		flag->length = 5;
	else if ((*format == 'l' && *(format + 1) == 'l') || *format == 'j')
		flag->length = flag->length > 4 ? flag->length : 4;
	else if ((*format == 'l' && *(format + 1) != 'l') || *format == 'z')
		flag->length = flag->length > 3 ? flag->length : 3;
	else if (*format == 'h' && *(format + 1) != 'h')
		flag->length = flag->length > 2 ? flag->length : 2;
	else if (*format == 'h' && *(format + 1) == 'h')
		flag->length = flag->length > 1 ? flag->length : 1;
	else
		return (more(format, flag, ap));
	if (*format == format[1])
		return (2);
	return (1);
}

static int	fields(int *j, char *format, va_list ap, t_flags *flag)
{
	int		last;

	if (*format == 'U' || *format == 'O' || *format == 'D')
		flag->length = 3;
	if (*format == 's' || *format == 'c' || *format == 'p' || *format == 'd' ||
		*format == 'X' || *format == 'x' || *format == 'f' || *format == 'i' ||
		*format == 'o' || *format == 'u' || *format == 'D' || *format == 'O' ||
		*format == 'U' || *format == '%')
		*j += types(format, ap, flag);
	else
	{
		last = flags(format, flag, ap);
		if (!last)
		{
			if (!*format)
				return (flag->size);
			*j += types(format, ap, flag);
			return (++flag->size);
		}
		flag->zero = flag->left ? 0 : flag->zero;
		flag->size += last;
		flag->left = flag->width < 0 ? 1 : flag->left;
		fields(j, format + last, ap, flag);
	}
	return (flag->size);
}

int			ft_printf(char *format, ...)
{
	va_list	ap;
	int		j;
	t_flags	flag;

	va_start(ap, format);
	j = 0;
	while (*format)
	{
		if (*format == '%')
		{
			flag = (t_flags) {0, 0, 0, 0, 0, -1, 0, 1};
			format += fields(&j, format + 1, ap, &flag);
			if (!*format)
				return (j);
		}
		else
		{
			ft_putchar(*format);
			j++;
		}
		format++;
	}
	va_end(ap);
	return (j);
}
