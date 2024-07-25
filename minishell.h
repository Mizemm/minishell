/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:19:27 by mizem             #+#    #+#             */
/*   Updated: 2024/07/24 20:07:53 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "utils/ft_printf/ft_printf.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


void	parse(char *line);

char	*ft_strchr(const char *s, int c);
int		ft_strlen(char *str);
void	ft_strncpy(char *s1, char *s2, int len);
char	*ft_strdup(char *src);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *str, char c);


// typedef struct s_cmd
// {
// 	char *command;
// 	char *flag;
// 	char *directory;
// }	t_cmd;

typedef struct s_token
{
    char *type;
    
    char *value;
    void *next;
} t_token;

#endif