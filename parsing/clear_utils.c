/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:36:27 by mizem             #+#    #+#             */
/*   Updated: 2024/10/29 21:37:44 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_lexer_list(t_lexer *head)
{
	t_lexer	*tmp;

	while (head != NULL)
	{
		tmp = head;
		if (*(tmp->content))
			free(tmp->content);
		head = head->next;
		free(tmp);
	}
	head = NULL;
}

void	clear_env_list(t_env **head)
{
	t_env	*tmp;

	while (*head)
	{
		tmp = *head;
		if ((*head)->name)
			free((*head)->name);
		if ((*head)->value)
			free((*head)->value);
		*head = tmp->next;
		free(tmp);
	}
	*head = NULL;
}

void	clear_output_list(t_out **head)
{
	t_out	*tmp;

	while (*head)
	{
		tmp = *head;
		if ((*head)->output)
			free((*head)->output);
		*head = tmp->next;
		free(tmp);
	}
	*head = NULL;
}

void	clear_cmd_list(t_cmd *head)
{
	t_cmd	*tmp;

	while (head)
	{
		tmp = head;
		if (tmp->command)
			free(tmp->command);
		if (tmp->path)
			free(tmp->path);
		if (tmp->args)
			ft_free(tmp->args);
		if (tmp->input_file)
			ft_free(tmp->input_file);
		if (tmp->output_files)
			clear_output_list(&tmp->output_files);
		if (tmp->heredoc_delimiter)
			ft_free(tmp->heredoc_delimiter);
		if (tmp->heredoc_content)
			free(tmp->heredoc_content);
		head = head->next;
		free(tmp);
	}
}
