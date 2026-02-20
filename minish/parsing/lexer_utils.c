/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:44:37 by mizem             #+#    #+#             */
/*   Updated: 2024/10/18 23:53:14 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	special_char(char c)
{
	if (c == ' ' || c == '\t' || c == '\'' || c == '\"' || c == '|'
		| c == '<' || c == '>')
		return (1);
	return (0);
}

int	find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	valid_syntax_condition(t_lexer *list, int flag)
{
	if (flag == 1)
	{
		if ((list->type == REDIR_IN || list->type == REDIR_OUT 
				|| list->type == HERE_DOC || list->type == APPEND 
				|| list->type == PIPE_LINE) && list->next == NULL)
			return (1);
	}
	else if (flag == 2)
	{
		if ((list->type == REDIR_IN || list->type == REDIR_OUT 
				|| list->type == HERE_DOC || list->type == APPEND) 
			&& (next_false(list->next) || (list->next->type == WHITE_SPACE 
					&& next_false(list->next->next))))
			return (1);
	}
	else if (flag == 3)
	{
		if (list->err_quotes == true || 
			(list->type == PIPE_LINE && pipe_syntax(list->content) == 1))
			return (1);
	}
	return (0);
}
