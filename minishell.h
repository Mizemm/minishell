/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:19:27 by mizem             #+#    #+#             */
/*   Updated: 2024/07/20 12:55:36 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "utils/ft_printf/ft_printf.h"
#include <stdio.h>
#include <stdlib.h>


void	ft_strncpy(char *s1, char *s2, int len);

typedef struct s_cmd
{
	char *commad;
	char *flag;
	char *directory;
}	t_cmd;











#endif