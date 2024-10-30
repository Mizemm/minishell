/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:38:43 by mizem             #+#    #+#             */
/*   Updated: 2024/10/30 17:06:36 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

t_lexer	*add_node(char *str)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->content = str;
	node->next = NULL;
	return (node);
}

t_out	*add_file(char *str, int type)
{
	t_out	*node;

	node = malloc(sizeof(t_out));
	if (!node)
		return (NULL);
	node->output = str;
	node->type = type;
	node->next = NULL;
	return (node);
}
