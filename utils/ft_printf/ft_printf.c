/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 10:27:08 by mizem             #+#    #+#             */
/*   Updated: 2024/03/22 04:57:31 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check(char c, va_list ap, int count)
{
	count = 0;
	if (c == '%')
		count += ft_putchar('%');
	else if (c == 'c')
		count += ft_putchar(va_arg(ap, int));
	else if (c == 's')
		count += ft_putstr(va_arg(ap, char *));
	else if (c == 'p')
	{
		count += ft_putstr("0x");
		count += ft_hex(va_arg(ap, unsigned long));
	}
	else if (c == 'd' || c == 'i')
		count += ft_putnbr(va_arg(ap, int));
	else if (c == 'u')
		count += ft_unsignednbr(va_arg(ap, unsigned int));
	else if (c == 'x')
		count += ft_hex(va_arg(ap, unsigned int));
	else if (c == 'X')
		count += ft_upperhex(va_arg(ap, unsigned int));
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		count;

	va_start(ap, str);
	i = 0;
	count = 0;
	if (write(1, 0, 0) == -1)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += check(str[i + 1], ap, count);
			i++;
		}
		else
			count += ft_putchar(str[i]);
		i++;
	}
	return (count);
}
