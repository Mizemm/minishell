/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 02:49:24 by abdennac          #+#    #+#             */
/*   Updated: 2024/07/23 12:32:48 by mizem            ###   ########.fr       */
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
	tokens.directory = lines[2];
	
	printf("-%s-\n", tokens.command);
	printf("-%s-\n", tokens.flag);
	printf("-%s-\n", tokens.directory);
}

