/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 20:08:56 by mizem             #+#    #+#             */
/*   Updated: 2024/10/07 23:26:53 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	itoa_len(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			len;
	int			r;
	long int	holder;
	char		*str;

	len = itoa_len(n);
	r = len;
	holder = n;
	str = malloc((r + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[r] = '\0';
	if (holder < 0)
		holder *= -1;
	while (r > 0)
	{
		str[r - 1] = holder % 10 + 48;
		holder = holder / 10;
		r--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
