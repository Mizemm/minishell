/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:19:27 by mizem             #+#    #+#             */
/*   Updated: 2024/07/26 14:25:22 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "utils/ft_printf/ft_printf.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_list
{
    char *content;
    struct s_list *next;
}	t_list;

void	ft_lstclear(t_list **lst, void (*del)(void *));
int     ft_lstsize(t_list *lst);

int		ft_strlen(char *str);
int     ft_isalnum(int c);
char	*ft_strchr(const char *s, int c);
int     ft_strncmp(const char *s1, const char *s2);
void	ft_strncpy(char *s1, char *s2, int len);
char	*ft_strdup(char *src);
char	*ft_strjoin(char *s1, char *s2);
int     count_wc(char *str, char c);
char	**ft_split(char *str, char c);

/* ########################################################################### */

typedef struct s_cmd {
 char *command; // The command name (e.g., "echo", "ls")
 char *path; // The full path to the command (e.g., "/bin/echo", "/bin
 char **args; // Array of arguments including the command
 int arg_count; // Number of arguments
 char *input_file; // For input redirection (<)
 char *output_file; // For output redirection (>)
//  char *append_file; // For append redirection (>>)
//  char *heredoc_delimiter; // For heredoc (<<)
//  char *heredoc_content; // Content of heredoc
//  int pipe_out; // 1 if this command pipes to next, 0 otherwise
 struct s_cmd *next; // Pointer to next command in pipeline
} t_cmd;

char **environment(char **env);
void	parse(char *line);

#endif