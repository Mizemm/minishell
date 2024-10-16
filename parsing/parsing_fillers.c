/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fillers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:48:21 by mizem             #+#    #+#             */
/*   Updated: 2024/10/16 23:51:53 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	fill_input_file(t_lexer **lexer, t_cmd *tmp_list)
{
	while ((*lexer) && (*lexer)->type != WORD && (*lexer)->type != ENV)
		(*lexer) = (*lexer)->next;
	tmp_list->input_file[tmp_list->in_index++] = ft_strdup((*lexer)->content);
	tmp_list->input_file[tmp_list->in_index] = NULL;
	(*lexer) = (*lexer)->next;
}

void	fill_output_file(t_lexer **lexer, t_cmd *tmp_list)
{
	while ((*lexer) && (*lexer)->type != WORD && (*lexer)->type != ENV)
		(*lexer) = (*lexer)->next;
	tmp_list->output_file[tmp_list->out_index++] = ft_strdup((*lexer)->content);
	tmp_list->output_file[tmp_list->out_index] = NULL;
	(*lexer) = (*lexer)->next;
}

void	fill_append_file(t_lexer **lexer, t_cmd *tmp_list)
{
	while ((*lexer) && (*lexer)->type != WORD && (*lexer)->type != ENV)
		(*lexer) = (*lexer)->next;
	tmp_list->append_file[tmp_list->app_index++] = ft_strdup((*lexer)->content);
	tmp_list->append_file[tmp_list->app_index] = NULL;
	(*lexer) = (*lexer)->next;
}

void	fill_heredoc(t_lexer **lexer, t_cmd *tmp_list)
{
	while ((*lexer) && (*lexer)->type != WORD && (*lexer)->type != ENV)
		(*lexer) = (*lexer)->next;
	tmp_list->heredoc_delimiter[tmp_list->her_index++] = ft_strdup((*lexer)->content);
	tmp_list->heredoc_delimiter[tmp_list->her_index] = NULL;
	(*lexer) = (*lexer)->next;
}

void	fill_args(t_lexer **lexer, t_cmd *tmp_list)
{
	tmp_list->args[tmp_list->arg_index++] = ft_strdup((*lexer)->content);
	tmp_list->args[tmp_list->arg_index] = NULL;
	(*lexer) = (*lexer)->next;
}
