/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:22:39 by abdennac          #+#    #+#             */
/*   Updated: 2024/07/31 15:23:59 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void tokenize(char *input, t_main *main, int *token_count)
{
	char *buffer = malloc(ft_strlen(input) + 1);
	if (!buffer)
		error("Buffer allocation failed");
	int buf_idx;

	while (*input != '\0')
	{
		if (spc_check(*input))
			input++;

		buf_idx = 0;
		// Tokenize FLAG
		if (*input == '-' && ft_isalnum(*(input + 1)))
		{
			while (*input && !spc_check(*input))
				buffer[buf_idx++] = *input++;
			buffer[buf_idx] = '\0';
			ft_lstadd_back_token(&main->tokens, new_t_token("FLAG", buffer));
		}

		// Tokenize OPERATOR
		else if (ft_strchr("|&><=", *input))
		{
			buffer[buf_idx++] = *input++;
			buffer[buf_idx] = '\0';
			ft_lstadd_back_token(&main->tokens, new_t_token("OPERATOR", buffer));
		}

		// Tokenize QUOTED_STRING
		else if (*input == '"' || *input == '\'')
		{
			char quote = *input++;
			while (*input && *input != quote)
				buffer[buf_idx++] = *input++;
			if (*input == quote)
				input++;
			buffer[buf_idx] = '\0';
			ft_lstadd_back_token(&main->tokens, new_t_token("QUOTED_STRING", buffer));
		}

		// Tokenize VARIABLE
		else if (*input == '$' && ft_isalnum(*(input + 1)))
		{
			buffer[buf_idx++] = *input++;
			while (ft_isalnum(*input) || *input == '_')
				buffer[buf_idx++] = *input++;
			buffer[buf_idx] = '\0';
			ft_lstadd_back_token(&main->tokens, new_t_token("VARIABLE", buffer));
		}

		// Tokenize COMMAND/ARGUMENT
		else
		{
			while (*input && !spc_check(*input) && !ft_strchr("|&><=", *input))
				buffer[buf_idx++] = *input++;
			buffer[buf_idx] = '\0';

			if (*token_count == 0 || ft_strcmp((main->tokens)[*token_count - 1].type, "OPERATOR") == 0)
				ft_lstadd_back_token(&main->tokens, new_t_token("COMMAND", buffer));
			else
				ft_lstadd_back_token(&main->tokens, new_t_token("ARGUMENT", buffer));
		}
	}

	free(buffer);
	buffer = NULL;
}

int count_ac(t_token *tokens)
{
	int i = 0;
	while (tokens && tokens->value[0] != '|')
	{
		i++;
		tokens = tokens->next;
	}
	return (i);
}

void create_list(t_cmd *cmd, t_token *tokens)
{
	int i = 0;

	cmd = malloc(sizeof(t_cmd));
	cmd->arg_count = count_ac(tokens);
	cmd->args = malloc((cmd->arg_count * sizeof(char *)) + 1);
	cmd->args[cmd->arg_count - 1] = NULL;
	if (!cmd->args)
		error("command allocation failed");

	while (tokens && tokens->value[0] != '|')
	{
		cmd->args[i] = ft_strdup(tokens->value);
		tokens = tokens->next;
		// if (ft_strcmp(tokens->type, "COMMAND"))
		//     cmd->command = ft_strdup(tokens->value);
		i++;
	}
	i = -1;
	while(cmd->args[++i])
		printf("*** %s\n", cmd->args[i]);
}
