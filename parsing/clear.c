/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:15:50 by mizem             #+#    #+#             */
/*   Updated: 2024/10/13 18:06:49 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void clear_cmd_list(t_cmd *head)
{
    t_cmd *tmp;

    while (head != NULL)
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
void clear_lexer_list(t_lexer *head)
{
    t_lexer *tmp;

    while (head != NULL)
    {
        tmp = head;
        if (*(tmp->content))
            free(tmp->content);
        head = head->next;
        free(tmp);
    }
}
void clear_env_list(t_env *head)
{
    t_env *tmp;

    while (head != NULL)
    {
        tmp = head;
        if (tmp->value)
            free(tmp->value);
        if (tmp->name)
            free(tmp->name);
        head = head->next;
        free(tmp);
    }
}
void clear(t_main *main, t_lexer *lexer, char *line)
{
    if (main->cmd)
    {
        clear_cmd_list(main->cmd);
        free(main);
    }
    if (lexer)
        clear_lexer_list(lexer);
    if(*line)
        free(line);
}
