/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_upperhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 10:22:52 by mizem             #+#    #+#             */
/*   Updated: 2024/01/24 10:50:47 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_upperhex(unsigned long int x)
{
	int		count;
	char	*arr;

	count = 0;
	arr = "0123456789ABCDEF";
	if (x < 16)
		count += write(1, &arr[x], 1);
	else
	{
		count += ft_upperhex(x / 16);
		count += ft_upperhex(x % 16);
	}
	return (count);
}
