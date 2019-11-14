/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:43:35 by mfrias            #+#    #+#             */
/*   Updated: 2019/06/09 13:29:31 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_hexa(unsigned long long value)
{
	char	*num;
	int		i;

	if (value == 0)
		return ("0");
	num = ft_strnew(1);
	i = 0;
	while (value > 0)
	{
		if (value % 16 >= 10)
			num[i] = ('a' + value % 16 % 10);
		else
			num[i] = ('0' + value % 16);
		i++;
		value = value / 16;
	}
	num[i] = '\0';
	num = ft_strrev(num);
	return (num);
}
