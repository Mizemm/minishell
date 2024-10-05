/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:23:23 by mizem             #+#    #+#             */
/*   Updated: 2024/09/29 18:41:32 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char *s, int start, int len)
{
	char	*dst;
	int	i;
	int	srclen;
	int	khawi;

	i = 0;
	if (!s)
		return (NULL);
	srclen = ft_strlen(s); 
	khawi = len;
	if (start >= srclen)
		return (ft_strdup(""));
	if (srclen <= len + start)
		khawi = srclen - start;
	dst = (char *)malloc((khawi + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (i < khawi)
	{
		dst[i] = s[start + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
