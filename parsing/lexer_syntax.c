/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:52:58 by mizem             #+#    #+#             */
/*   Updated: 2024/10/14 16:55:09 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int pipe_syntax(char *str)
{
	int i = 0;
	int j = 0;
	while (str[i])
	{
		if (str[i] == '|')
			j++;
		i++;
	}
	if (j > 1)
		return (1);
	return (0);
}
int in_redirections_syntax(char *str)
{
	int i = 0;
	int j = 0;
	while (str[i])
	{
		if (str[i] == '<')
			j++;
		i++;
	}
	return (j);
}
	int out_redirections_syntax(char *str)
{
	int i = 0;
	int j = 0;
	while (str[i])
	{
		if (str[i] == '>')
			j++;
		i++;
	}
	return (j);
}
int next_false(t_lexer *list)
{
		if (!list)
			return (1);
		if (list->type == PIPE_LINE || list->type == REDIR_IN || list->type == REDIR_OUT || list->type == APPEND || list->type == HERE_DOC)
			return (1);
		else
			return (0);
}
bool syntax_error(t_lexer *list)
{
	if (list->type == PIPE_LINE)
		return (true);
	while (list)
	{
		if ((list->type == REDIR_IN || list->type == REDIR_OUT || list->type == HERE_DOC 
			|| list->type == APPEND || list->type == PIPE_LINE) && list->next == NULL)
			return (true);
		if ((list->type == REDIR_IN || list->type == REDIR_OUT || list->type == HERE_DOC 
			|| list->type == APPEND) && (next_false(list->next) || (list->next->type == WHITE_SPACE && next_false(list->next->next))))
			return (true);
		else if (list->err_quotes == true || (list->type == PIPE_LINE && pipe_syntax(list->content) == 1))
				return (true);
		else if (list->type == REDIR_IN || list->type == HERE_DOC)
		{
			if (in_redirections_syntax(list->content) > 2 || list->next->type == REDIR_OUT)
				return (true);
		}
		else if (list->type == REDIR_OUT || list->type == APPEND)
		{
			if (out_redirections_syntax(list->content) > 2 || list->next->type == REDIR_IN)
				return (true);
		}
		list = list->next;
	}
	return (false);
}
