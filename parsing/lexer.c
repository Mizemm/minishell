/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:01:42 by mizem             #+#    #+#             */
/*   Updated: 2024/11/01 01:01:50 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes_tokenize(t_lexer **list, char *str, int i, int j)
{
	t_lexer	*node;
	bool	err_q;
	char	c;

	err_q = false;
	c = str[i + j];
	j++;
	while (str[i + j] && str[i + j] != c)
		j++;
	if (str[i + j] == '\0')
		err_q = true;
	else
		j++;
	node = add_node(ft_strsize_cpy(&str[i + 1], j - 2));
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

int	special_tokenize(t_lexer **list, char *str, int i, int j)
{
	t_lexer	*node;
	bool	err_q;
	char	c;

	err_q = false;
	c = str[i + j];
	if ((c == '\"' || c == '\'') && str[i + j])
		return (quotes_tokenize(list, str, i, j));
	else
	{
		while (str[i + j] == c)
		{
			j++;
			if ((c == '\"' || c == '\''))
				break ;
		}
	}
	node = add_node(ft_strsize_cpy(&str[i], j));
	node->state = GENERAL;
	node->len = j;
	node->in_quotes = false;
	node->err_quotes = err_q;
	return (ft_lstadd_back2(list, node), j);
}

int	normal_tokenize(char *str, t_lexer **list, int i)
{
	int		j;
	t_lexer	*node;

	j = 0;
	while (str[i + j] && !special_char(str[i + j]))
		j++;
	node = add_node(ft_strsize_cpy(&str[i], j));
	node->state = GENERAL;
	node->len = j;
	ft_lstadd_back2(list, node);
	return (j);
}

t_lexer	*tokenize(char *str, t_main *main)
{
	t_lexer	*list;
	int		i;
	int		j;

	i = 0;
	str = ft_strtrim(str, " \t");
	list = NULL;
	while (str[i])
	{
		j = 0;
		if (special_char(str[i]))
			i += special_tokenize(&list, str, i, j);
		else
			i += normal_tokenize(str, &list, i);
	}
	give_type(list);
	if (list)
		list->syntax_error = syntax_error(list);
	expand(list, main);
	re_lex(list);
	free(str);
	return (list);
}
