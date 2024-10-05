/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:22:11 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/01 09:22:33 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

t_env	*ft_lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(t_env **head, t_env *new)
{
	t_env *tmp;

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
		tmp = ft_lstlast_env(*head);
		tmp->next = new;
	}	
}
