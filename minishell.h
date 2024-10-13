/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:19:27 by mizem             #+#    #+#             */
/*   Updated: 2024/10/13 18:42:10 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_expo
{
	char			*value;
	char			*name;
	int				is_export;
	struct s_expo	*next;
}					t_expo;

typedef struct s_env
{
	char			*value;
	char			*name;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char			*command;
	char			*path;
	char			**args;
	int				arg_count;
	char			**input_file;
	char			**output_file;
	char			**append_file;
	char			**heredoc_delimiter;
	char			*heredoc_content;
	int				pipe_out;
	int				stdin_backup;
	int				stdout_backup;
	struct s_cmd	*next;
}					t_cmd;

enum e_type
{
	WORD = -1,
	WHITE_SPACE = ' ',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	APPEND,
};

enum e_state
{
	IN_QUOTE = '\'',
	IN_DQUOTE = '\"',
	GENERAL,
};

typedef struct s_lexer
{
	char			*content;
	int				len;
	bool			in_quotes;
	bool			err_quotes;
	bool			syntax_error;
	enum e_type		type;
	enum e_state	state;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}					t_lexer;

typedef struct s_main
{
	int				exit_status;
	t_cmd			*cmd;
	t_env			*env;
	t_expo			*export;
	char			**full_env;
}					t_main;

/* LIBFT FUNCTIONS */

int					ft_strlen(char *str);
int					ft_isalnum(int c);
char				*ft_strchr(char *s, int c);
int					ft_strcmp(char *s1, char *s2);
int					ft_atoi(char *str);
void				ft_strncpy(char *s1, char *s2, int len);
char				*ft_strncoco(char *str, int size);
char				*ft_strdup(char *src);
char				*ft_substr(char *s, int start, int len);
char				*ft_strtrim(char *s1, char *set);
char				*ft_strjoin(char *s1, char *s2);
int					count_wc(char *str, char c);
char				**ft_split(char *str, char c);
char				**pipe_split(char *str, char c);
void				ft_putstr_fd(char *s, int fd);
void				*ft_free(char **str);
void				ft_lstadd_back(t_cmd **head, t_cmd *new);
void				ft_lstadd_back2(t_lexer **head, t_lexer *new);
char				*ft_itoa(int n);
t_lexer				*add_node(char *str);

/* PARSING FUNCTIONS */

void				clear_cmd_list(t_cmd *head);
int					special_char(char c);
int					path_check(char *s);
char				**environment(char *env);
char				*return_path(char **ev, char *str);
t_cmd				*create_list(t_cmd *list, t_lexer *lexer, char **ev);
t_lexer				*tokenize(char *str, t_main *main);
void				expand(t_lexer *list, t_main *main);
int					count_redir_out(t_lexer *list);
int					count_redir_in(t_lexer *list);
int					count_her(t_lexer *list);
int					count_append(t_lexer *list);
int					count_args(t_lexer *list);
void				clear(t_main *main, t_lexer *lexer, char *line);
int					valid_name(char c);
int					heredoc_breakers(char c);
void				fill_node(t_lexer **list, char *result);
void				skip_her(t_lexer **list, char *result);

/* EXECUTION FUNCTIONS */

void				handle_input_redirection(t_cmd *cmd, int *prev_pipe_fd);
void				handle_output_redirection(t_cmd *cmd, int *pipe_fd);
int					check_if_builtin(char *str);
void				execute_command(t_main *main);
void				redirections_setup(t_cmd *cmd, 
						int prev_pipe[2], int curr_pipe[2]);
void				pipe_setup(t_cmd *cmd, int prev_pipe[2], int curr_pipe[2]);
void				simple_exec(t_main *main);
void				simple_redirections(t_cmd *cmd);
void				simple_cleanup(t_cmd *cmd);
void				execute_builtins(t_main *main);
void				error(char *str);
t_env				*ft_lstlast_env(t_env *lst);
void				ft_lstadd_back_env(t_env **head, t_env *new);
void				update_env_value(t_env **env, char *name, char *value);
int					is_export(char **split, t_main *main);
void				print_export(t_main *main);
int					check_export(char **split);
void				handle_signals(void);

/* A77 */

void				exec_echo(t_main *main);
void				excec_pwd(void);
void				exec_env(t_main *main);
int					exec_cd(t_main *main);
void				exec_exit(t_main *main);
void				exec_export(t_main *main);
void				exec_unset(t_main *main);

#endif