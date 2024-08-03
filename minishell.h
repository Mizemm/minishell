/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:19:27 by mizem             #+#    #+#             */
/*   Updated: 2024/08/03 15:15:44 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// void				ft_lstclear(t_list **lst, void (*del)(void *));
// int					ft_lstsize(t_list *lst);

int					ft_strlen(char *str);
int					ft_isalnum(int c);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(char *s1, char *s2);
void				ft_strncpy(char *s1, char *s2, int len);
char				*ft_strdup(char *src);
char				*ft_strjoin(char *s1, char *s2);
int					count_wc(char *str, char c);
char				**pipe_split(char *str, char c);

/* ################################################################### */

typedef struct s_cmd
{
	char	*command;
	char	*path;
	char	**args;
	int		arg_count;
	char	*input_file;        // For input redirection (<)
	char	*output_file;       // For output redirection (>)
	char	*append_file;       // For append redirection (>>)
	char	*heredoc_delimiter; // For heredoc (<<)
	char	*heredoc_content;   // Content of heredoc
	int		pipe_out;            // 1 if command pipes to next, 0 otherwise
	char	**environment;
	struct s_cmd *next;      // Pointer to next command in pipeline
}					t_cmd;

void 				execute_command(t_cmd *commands);
void				ft_lstadd_back(t_cmd **head, t_cmd *new);
int					count_ac(char **str);
char				**environment(char *env);
void				parse(char *line);
t_cmd				*create_list(t_cmd *list, char *tokens, char **ev, int flag);

#endif