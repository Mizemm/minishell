/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:38:04 by mizem             #+#    #+#             */
/*   Updated: 2024/10/14 23:09:05 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_name(char c)
{
	if ((c >= 48 && c <= 58) || (c >= 65 && c <= 90) 
		|| (c >= 97 && c <= 122) || c == '_')
		return (1);
	return (0);
}

int	heredoc_breakers(char c)
{
	if (c == '>' || c == '<' || c == '\t' || c == ' ')
		return (1);
	return (0);
}

void	fill_node(t_lexer **list, char *result)
{
	free((*list)->content);
	(*list)->content = ft_strdup(result);
}

void	skip_her(t_lexer **list, char *result)
{
	while (heredoc_breakers((*list)->content[0]) != 1 && (*list)->next)
		(*list) = (*list)->next;
	if (!(*list)->next)
		free(result);
}

int	valid_condition(t_lexer *list)
{
	if (list->prev && list->prev->prev && (list->prev->type == HERE_DOC 
			|| (list->prev->prev->type == HERE_DOC 
				&& list->prev->type == WHITE_SPACE)))
		return (1);
	else
		return (0);
}
