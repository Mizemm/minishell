/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:03:50 by mizem             #+#    #+#             */
/*   Updated: 2024/07/26 13:37:35 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_lstdelone(t_list *lst, void (*del)(void *))
{
        if (!lst || !del)
                return ;
        del(lst->content);
        free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*to_delete;

	if (!lst || !del)
		return ;
	while ((*lst) != NULL)
	{
		to_delete = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(to_delete, del);
	}
}
