/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:39:38 by mizem             #+#    #+#             */
/*   Updated: 2024/10/30 21:51:28 by abdennac         ###   ########.fr       */
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
	t_cmd	*tmp;

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

t_lexer	*ft_lstlast2(t_lexer *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back2(t_lexer **head, t_lexer *new)
{
	t_lexer	*tmp;

	tmp = NULL;
	if (!head || !new)
		return ;
	new->prev = NULL;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = ft_lstlast2(*head);
	new->prev = tmp;
	tmp->next = new;
}
