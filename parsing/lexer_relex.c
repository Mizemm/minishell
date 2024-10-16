/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_relex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:42:19 by mizem             #+#    #+#             */
/*   Updated: 2024/10/15 17:56:30 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	re_lex_2(t_lexer **list)
{
	while ((*list))
	{
		if ((*list)->type == WORD || (*list)->type == ENV)
			break ;
		(*list) = (*list)->next;
	}
}

void	re_lex_3(t_lexer **list, t_lexer *head)
{
	t_lexer	*tmp;
	char	*new_str;

	new_str = NULL;
	new_str = ft_strjoin((*list)->content, (*list)->next->content);
	free((*list)->content);
	(*list)->content = ft_strdup(new_str);
	free(new_str);
	if ((*list)->next->next != NULL)
	{
		tmp = (*list)->next->next;
		free((*list)->next);
		(*list)->next = tmp;
	}
	else if ((*list)->next != NULL)
	{
		free((*list)->next);
		(*list)->next = NULL;
	}
	(*list) = head;
}

void	re_lex(t_lexer *list)
{
	t_lexer	*head;

	head = list;
	while (list != NULL)
	{
		if (flag(list) == 2)
			re_lex_2(&list);
		else if (flag(list) == 0 && flag(list->next) == 0)
			re_lex_3(&list, head);
		else
			list = list->next;
	}
}
