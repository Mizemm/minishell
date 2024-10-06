/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:01:42 by mizem             #+#    #+#             */
/*   Updated: 2024/10/06 19:46:28 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int special_char(char c)
{
	if (c == ' ' || c == '\t' || c == '\'' || c == '\"' || c == '|'
		| c == '<' || c == '>')
		return (1);
	return (0);
}
int find_dollar(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

enum e_type add_type(t_lexer *list)
{
	int flag;

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
void give_type(t_lexer *list)
{
	t_lexer *tmp;
	
	tmp = list;
	while (tmp)
	{
		tmp->type = add_type(tmp);
		tmp = tmp->next;
	}
}
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
void	re_lex_0(t_lexer **list)
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

void bf_null(t_lexer **list)
{
	free((*list)->next);
	(*list)->next = NULL;
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
			re_lex_0(&list);
			if (list->next->next != NULL)
			{
				tmp = list->next->next;
				free(list->next);
				list->next = tmp;
			}
			else if (list->next != NULL)
				bf_null(&list);
			list = head;
		}
		else
			list = list->next;
	}
}
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
	return (list);
}
