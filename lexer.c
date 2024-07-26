/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:22:39 by abdennac          #+#    #+#             */
/*   Updated: 2024/07/26 13:37:55 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void error(char *str)
{
	ft_printf("%s\n", str);
	exit(1);
}

int spc_check(int c)
{
	if (c == ' ')
		return (1);
	return (0);
}

void *ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

char *ft_strchr(const char *s, int c)
{
	while ((*s != '\0') && (*s != c))
	{
		s++;
	}
	if (*s == c)
	{
		return ((char *)s);
	}
	return ((char *)NULL);
}

void add_token(t_token **tokens, int *token_count, char *type, char *value)
{
	t_token *new_token = malloc((*token_count + 1) + sizeof(t_token));
	if (!new_token)
		error("token allocation failed");
	if (*tokens)
	{
		ft_memcpy(new_token, *tokens, *token_count * sizeof(t_token));
		free(*tokens);
	}
	new_token[*token_count].type = ft_strdup(type);
	new_token[*token_count].value = ft_strdup(value);
	if (!new_token[*token_count].type || !new_token[*token_count].type)
		error("type / value allocation failed");
	*tokens = new_token;
	(*token_count)++;
}

void tokenize(char *input, t_token **tokens, int *token_count)
{
	int i;
	char *buffer;
	int buff_i;
	char quote;

	buffer = malloc(ft_strlen(input) + 1);
	if (!buffer)
		error("buffer allocation failed");

	i = -1;
	while (input[++i])
	{
		if (spc_check(input[i]))
			i++;

		buff_i = 0;
		// tokenize flags
		if (input[i] == '-' && isalnum(input[i + 1]))
		{
			while (input[i] && !spc_check(input[i]))
				buffer[buff_i++] = input[i++];
			buffer[buff_i] = '\0';
			add_token(tokens, token_count, "FLAG", buffer);
		}
		// tokenize operator
		else if (ft_strchr("|&><=", input[i]))
		{
			buffer[buff_i++] = input[i++];
			buffer[buff_i] = '\0';
			add_token(tokens, token_count, "OPERATOR", buffer);
		}
		// tokenize quoted string
		else if (input[i] == '"' || input[i] == '\'')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				buffer[buff_i++] = input[i++];
			if(input[i] == quote)
				i++;
			buffer[buff_i] = '\0';
			 add_token(tokens, token_count, "QUOTED_STRING", buffer);
		}
		// tokenize variables
		else if ()
	}
	
	free(buffer);
}