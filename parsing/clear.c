/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:15:50 by mizem             #+#    #+#             */
/*   Updated: 2024/09/27 11:57:39 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void dp_free(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void clear_cmd_list(t_cmd *head)
{
    t_cmd *tmp;
    // int i;

    while (head != NULL && head->next)
    {
        tmp = head;
        if (tmp->command)
            free(tmp->command);
        if (tmp->path)
            free(tmp->path);
        if (tmp->args)
			dp_free(tmp->args);
        if (tmp->input_file)
            free(tmp->input_file);
        if (tmp->output_file)
			dp_free(tmp->output_file);
        if (tmp->append_file)
            free(tmp->append_file);
        if (tmp->heredoc_delimiter)
            free(tmp->heredoc_delimiter);
        if (tmp->heredoc_content)
            free(tmp->heredoc_content);
        head = head->next;
        free(tmp);
    }
}
