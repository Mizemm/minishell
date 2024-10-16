/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:04:03 by mizem             #+#    #+#             */
/*   Updated: 2024/10/15 14:22:15 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

enum e_type	add_type(t_lexer *list)
{
	int	flag;

	flag = 0;
	if (list->state == IN_DQUOTE || list->state == IN_QUOTE)
		flag = 1;
	if ((find_dollar(list->content) == 1))
		return (ENV);
	else if ((list->content[0] == ' ' || list->content[0] == '	') && flag != 1)
		return (WHITE_SPACE);
	else if (list->content[0] == '|' && flag != 1)
		return (PIPE_LINE);
	else if ((ft_strcmp(list->content, "<<") == 0) && flag != 1)
		return (HERE_DOC);
	else if ((ft_strcmp(list->content, ">>") == 0) && flag != 1)
		return (APPEND);
	else if (list->content[0] == '<' && flag != 1)
		return (REDIR_IN);
	else if (list->content[0] == '>' && flag != 1)
		return (REDIR_OUT);
	else if (!special_char(list->content[0]))
		return (WORD);
	return (WORD);
}

int	flag(t_lexer *list)
{
	if (!list)
		return (3);
	if (list->type == WHITE_SPACE)
		return (1);
	else if (list->type == REDIR_IN)
		return (2);
	else if (list->type == REDIR_OUT)
		return (2);
	else if (list->type == HERE_DOC)
		return (2);
	else if (list->type == APPEND)
		return (2);
	else if (list->type == PIPE_LINE)
		return (2);
	return (0);
}

void	give_type(t_lexer *list)
{
	t_lexer	*tmp;

	tmp = list;
	while (tmp)
	{
		tmp->type = add_type(tmp);
		tmp = tmp->next;
	}
}
