/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 10:03:11 by mizem             #+#    #+#             */
/*   Updated: 2024/01/22 11:54:02 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hex(unsigned long int x)
{
	int		count;
	char	*arr;

	count = 0;
	arr = "0123456789abcdef";
	if (x < 16)
		count += write(1, &arr[x], 1);
	else
	{
		count += ft_hex(x / 16);
		count += ft_hex(x % 16);
	}
	return (count);
}
