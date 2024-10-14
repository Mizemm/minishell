/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:01:42 by mizem             #+#    #+#             */
/*   Updated: 2024/10/14 17:17:43 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int special_tokenize(t_lexer **list, char *str, int i, int j)
{
	t_lexer *node;
	bool err_q;
	char c;

	err_q = false;
	c = str[i + j];
	if ((c == '\"' || c == '\'') && str[i+j])
	{
		j++;
		while (str[i + j] && str[i + j] != c)
			j++;
		if (str[i + j] == '\0')
			err_q = true;
		else
			j++;
		node = add_node(ft_strncoco(&str[i+1], j-2));
		node->len = ft_strlen(node->content);
		node->in_quotes = true;
		node->err_quotes = err_q;
		if (c == '\"')
			node->state = IN_DQUOTE;
		else if (c == '\'')
			node->state = IN_QUOTE;
		ft_lstadd_back2(list, node);

		return (j);
	}
	else
	{
		while (str[i + j] == c)
		{
			j++;
			if ((c == '\"' || c == '\''))
				break ;
		}
	}
	node = add_node(ft_strncoco(&str[i], j));
	node->state = GENERAL;
	node->len = j;
	node->in_quotes = false;
	node->err_quotes = err_q;
	return (ft_lstadd_back2(list, node), j);
}

void	re_lex_1(t_lexer **list)
{
	char *new_str;
	
	new_str = NULL;
	new_str = ft_strjoin((*list)->content, (*list)->next->content);
	free((*list)->content);
	(*list)->content = ft_strdup(new_str);
	free(new_str);
}
void	re_lex_2(t_lexer **list)
{
	while((*list))
	{
		if ((*list)->type == WORD || (*list)->type == ENV)
			break ;
		(*list) = (*list)->next;
	}
}

void	re_lex(t_lexer *list)
{
	t_lexer *head;
	t_lexer *tmp;
	
	head = list;
	while (list != NULL)
	{
		if (flag(list) == 2)
			re_lex_2(&list);
		else if (flag(list) == 0 && flag(list->next) == 0)
		{
			re_lex_1(&list);
			if (list->next->next != NULL)
			{
				tmp = list->next->next;
				free(list->next);
				list->next = tmp;
			}
			else if (list->next != NULL)
			{
				free(list->next);
				list->next = NULL;
			}
			list = head;
		}
		else
			list = list->next;
	}
}

t_lexer *tokenize(char *str, t_main *main)
{
	t_lexer *node;
	t_lexer *list;
	int i;
	int j;

	i = 0;
	str = ft_strtrim(str, " ");
	list = NULL;
	while (str[i])
	{
		j = 0;
		if (special_char(str[i]))
		{
			i += special_tokenize(&list, str, i, j);
		}
		else
		{
			while (str[i + j] && !special_char(str[i + j]))
				j++;
			node = add_node(ft_strncoco(&str[i], j));
			node->state = GENERAL;
			node->len = j;
			
			ft_lstadd_back2(&list, node);
			if (!node)
				return (NULL);
			i = i + j;
		}
	}
	give_type(list);
	list->syntax_error = syntax_error(list);
	expand(list, main);
	re_lex(list);
	free(str);
	return (list);
}
