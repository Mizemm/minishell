/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:39:38 by mizem             #+#    #+#             */
/*   Updated: 2024/08/03 16:53:58 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_lstlast(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_cmd **head, t_cmd *new)
{
	t_cmd *tmp;

	tmp = NULL;	
	if (!head || !new)
		return ;
	else if (!*head)
	{
		*head = new;
		return ;
	}
	else
	{
		tmp = ft_lstlast(*head);
		tmp->next = new;
	}	
}
