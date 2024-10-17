/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_counters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:40:04 by mizem             #+#    #+#             */
/*   Updated: 2024/10/16 00:44:34 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(t_lexer *list)
{
	int	wc;

	wc = 0;
	while (list && list->type != PIPE_LINE)
	{
		if (list->type == WHITE_SPACE)
			list = list->next;
		else if (list->type == REDIR_IN || list->type == REDIR_OUT 
			|| list->type == APPEND || list->type == HERE_DOC)
		{
			while (list && list->type != WORD && list->type != ENV)
				list = list->next;
			list = list->next;
		}
		else
		{
			wc++;
			list = list->next;
		}
	}
	return (wc);
}

int	count_redir_out(t_lexer *list)
{
	int	wc;

	wc = 0;
	while (list && list->type != PIPE_LINE)
	{
		if (list->type == REDIR_OUT)
			wc++;
		list = list->next;
	}
	return (wc);
}

int	count_redir_in(t_lexer *list)
{
	int	wc;

	wc = 0;
	while (list && list->type != PIPE_LINE)
	{
		if (list->type == REDIR_IN)
			wc++;
		list = list->next;
	}
	return (wc);
}

int	count_her(t_lexer *list)
{
	int	wc;

	wc = 0;
	while (list && list->type != PIPE_LINE)
	{
		if (list->type == HERE_DOC)
			wc++;
		list = list->next;
	}
	return (wc);
}

int	count_append(t_lexer *list)
{
	int	wc;

	wc = 0;
	while (list && list->type != PIPE_LINE)
	{
		if (list->type == APPEND)
			wc++;
		list = list->next;
	}
	return (wc);
}
