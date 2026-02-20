/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:52:58 by mizem             #+#    #+#             */
/*   Updated: 2024/10/15 14:58:19 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_syntax(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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

int	in_redirections_syntax(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '<')
			j++;
		i++;
	}
	return (j);
}

int	out_redirections_syntax(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '>')
			j++;
		i++;
	}
	return (j);
}

int	next_false(t_lexer *list)
{
	if (!list)
		return (1);
	if (list->type == PIPE_LINE || list->type == REDIR_IN 
		|| list->type == REDIR_OUT || list->type == APPEND 
		|| list->type == HERE_DOC)
		return (1);
	else
		return (0);
}

bool	syntax_error(t_lexer *list)
{
	if (list->type == PIPE_LINE)
		return (true);
	while (list)
	{
		if (valid_syntax_condition(list, 1))
			return (true);
		if (valid_syntax_condition(list, 2))
			return (true);
		if (valid_syntax_condition(list, 3))
			return (true);
		if (list->type == REDIR_IN || list->type == HERE_DOC)
		{
			if (in_redirections_syntax(list->content) > 2 
				|| list->next->type == REDIR_OUT)
				return (true);
		}
		if (list->type == REDIR_OUT || list->type == APPEND)
		{
			if (out_redirections_syntax(list->content) > 2 
				|| list->next->type == REDIR_IN)
				return (true);
		}
		list = list->next;
	}
	return (false);
}
