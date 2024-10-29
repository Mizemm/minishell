/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 02:49:24 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/29 21:39:48 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize(t_cmd *cmd)
{
	cmd->command = NULL;
	cmd->path = NULL;
	cmd->args = NULL;
	cmd->arg_count = 0;
	cmd->input_file = NULL;
	cmd->heredoc_delimiter = NULL;
	cmd->output_files = NULL;
	cmd->heredoc_content = NULL;
	cmd->herdoc_flag = 0;
	cmd->pipe_out = 0;
	cmd->stdin_backup = 0;
	cmd->stdout_backup = 0;
	cmd->arg_index = 0;
	cmd->in_index = 0;
	cmd->out_index = 0;
	cmd->app_index = 0;
	cmd->her_index = 0;
	cmd->next = NULL;
}

void	allocate_list(t_cmd *list, t_lexer *lexer)
{
	if (count_args(lexer) > 0)
		list->args = malloc(sizeof(char *) * (count_args(lexer) + 1));
	if (count_redir_in(lexer) > 0)
		list->input_file = malloc(sizeof(char *) * (count_redir_in(lexer) + 1));
	if (count_her(lexer) > 0)
		list->heredoc_delimiter = malloc(sizeof(char *) 
				* (count_her(lexer) + 1));
}

void	fill_list(t_lexer **lexer, t_cmd *tmp_list)
{
	if ((*lexer)->type == WHITE_SPACE)
		(*lexer) = (*lexer)->next;
	else if ((*lexer)->type == REDIR_IN)
		fill_input_file(lexer, tmp_list);
	else if ((*lexer)->type == REDIR_OUT)
		fill_output_file(lexer, tmp_list);
	else if ((*lexer)->type == APPEND)
		fill_append_file(lexer, tmp_list);
	else if ((*lexer)->type == HERE_DOC)
		fill_heredoc(lexer, tmp_list);
	else
		fill_args(lexer, tmp_list);
}

t_cmd	*create_args(t_lexer **lexer, char **ev)
{
	t_cmd	*tmp_list;

	tmp_list = malloc(sizeof(t_cmd));
	if (!tmp_list)
		return (NULL);
	initialize(tmp_list);
	allocate_list(tmp_list, (*lexer));
	while ((*lexer) && (*lexer)->type != PIPE_LINE)
		fill_list(lexer, tmp_list);
	if (tmp_list->args)
	{
		tmp_list->command = ft_strdup(tmp_list->args[0]);
		if (ft_strchr(tmp_list->command, '/'))
		{
			tmp_list->path = ft_strdup(tmp_list->command);
			tmp_list->command = path_split(tmp_list->command, '/');
			if (access(tmp_list->path, X_OK) != 0)
			{
				free(tmp_list->path);
				tmp_list->path = NULL;
			}
		}
		else
			tmp_list->path = return_path(ev, tmp_list->command);
	}
	if ((*lexer) && (*lexer)->type == PIPE_LINE)
		tmp_list->pipe_out = 1;
	return (tmp_list);
}

t_cmd	*create_list(t_cmd *list, t_lexer *lexer, char **ev)
{
	t_lexer	*head;

	head = lexer;
	while (lexer && lexer->type != PIPE_LINE)
	{
		ft_lstadd_back(&list, create_args(&lexer, ev));
		if (lexer == NULL)
			break ;
		lexer = lexer->next;
	}
	lexer = head;
	if (ev)
		ft_free(ev);
	clear_lexer_list(lexer);
	return (list);
}
