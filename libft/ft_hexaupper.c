/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexaupper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrias <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 14:01:50 by mfrias            #+#    #+#             */
/*   Updated: 2019/05/24 14:22:18 by mfrias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_hexaupper(unsigned int value)
{
	char	*num;
	int		i;

	num = ft_strnew(1);
	i = 0;
	while (value > 0)
	{
		if (value % 16 >= 10)
			num[i] = ('A' + value % 16 % 10);
		else
			num[i] = ('0' + value % 16);
		i++;
		value = value / 16;
	}
	num = ft_strrev(num);
	return (num);
}
