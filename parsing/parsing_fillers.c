/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fillers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 01:34:46 by mizem             #+#    #+#             */
/*   Updated: 2024/10/29 21:41:10 by mizem            ###   ########.fr       */
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
	t_out	*node;

	node = NULL;
	while ((*lexer) && (*lexer)->type != WORD && (*lexer)->type != ENV)
		(*lexer) = (*lexer)->next;
	node = add_file(ft_strdup((*lexer)->content), 1);
	ft_lstadd_back3(&tmp_list->output_files, node);
	(*lexer) = (*lexer)->next;
}

void	fill_append_file(t_lexer **lexer, t_cmd *tmp_list)
{
	t_out	*node;

	node = NULL;
	while ((*lexer) && (*lexer)->type != WORD && (*lexer)->type != ENV)
		(*lexer) = (*lexer)->next;
	node = add_file(ft_strdup((*lexer)->content), 0);
	ft_lstadd_back3(&tmp_list->output_files, node);
	(*lexer) = (*lexer)->next;
}

void	fill_heredoc(t_lexer **lexer, t_cmd *tmp_list)
{
	while ((*lexer) && (*lexer)->type != WORD && (*lexer)->type != ENV)
		(*lexer) = (*lexer)->next;
	tmp_list->herdoc_flag = 0;
	if ((*lexer)->state == IN_QUOTE || (*lexer)->state == IN_DQUOTE)
		tmp_list->herdoc_flag = 1;
	tmp_list->heredoc_delimiter[tmp_list->her_index++] = 
		ft_strdup((*lexer)->content);
	tmp_list->heredoc_delimiter[tmp_list->her_index] = NULL;
	(*lexer) = (*lexer)->next;
}

void	fill_args(t_lexer **lexer, t_cmd *tmp_list)
{
	tmp_list->args[tmp_list->arg_index++] = ft_strdup((*lexer)->content);
	tmp_list->args[tmp_list->arg_index] = NULL;
	(*lexer) = (*lexer)->next;
}
