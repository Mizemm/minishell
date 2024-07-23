/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 02:49:24 by abdennac          #+#    #+#             */
/*   Updated: 2024/07/23 03:44:50 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// proof of consept to split the tokens
void	parse(char *line)
{
	t_cmd	tokens;

	char **lines = ft_split(line, ' ');
	
	tokens.command = lines[0];
	if (lines[1][0] == '-')
		tokens.flag = lines[1];
	tokens.directory= lines[2];
	
	printf("-%s-\n", tokens.command);
	printf("-%s-\n", tokens.flag);
	printf("-%s-\n", tokens.directory);
}

