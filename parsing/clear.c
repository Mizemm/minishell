/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:15:50 by mizem             #+#    #+#             */
/*   Updated: 2024/10/21 23:51:58 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (tmp->output_file)
			ft_free(tmp->output_file);
		if (tmp->append_file)
			ft_free(tmp->append_file);
		if (tmp->heredoc_delimiter)
			ft_free(tmp->heredoc_delimiter);
		if (tmp->heredoc_content)
			free(tmp->heredoc_content);
		head = head->next;
		free(tmp);
	}
}

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

void	clear(t_cmd *cmd, char *line)
{
	if (cmd)
		clear_cmd_list(cmd);
	if (*line)
		free(line);
}

void	clear_all(t_main **main)
{
	while ((*main)->env)
	{
		if ((*main)->env->name)
			free((*main)->env->name);
		if ((*main)->env->value)
			free((*main)->env->value);
		(*main)->env = (*main)->env->next;
	}
	if ((*main)->heredoc_files)
		ft_free((*main)->heredoc_files);
	(*main)->exit_status = 0;
	free(*main);
	*main = NULL;
}
