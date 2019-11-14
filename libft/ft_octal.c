/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_octal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 14:37:18 by mfrias            #+#    #+#             */
/*   Updated: 2019/06/09 13:28:34 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_octal(unsigned long long value)
{
	char				*num;
	int					i;
	unsigned long long	original;
	int					size;

	if (value == 0)
		return ("0");
	original = value;
	size = -1;
	while (original)
	{
		size++;
		original = original / 8;
	}
	num = ft_strnew(size);
	i = 0;
	while (value)
	{
		num[i] = ('0' + value % 8);
		i++;
		value = value / 8;
	}
	num[i] = '\0';
	num = ft_strrev(num);
	return (num);
}
