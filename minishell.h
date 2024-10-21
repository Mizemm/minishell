/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:19:27 by mizem             #+#    #+#             */
/*   Updated: 2024/10/21 23:50:44 by mizem            ###   ########.fr       */
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
	int				herdoc_flag;
	int				pipe_out;
	int				stdin_backup;
	int				stdout_backup;
	int				arg_index;
	int				in_index;
	int				out_index;
	int				app_index;
	int				her_index;
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
    int exit_status;
    t_cmd *cmd;
    t_env *env;
    t_expo *export;
    char **full_env;
    char **heredoc_files;
} t_main;

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
char				**ft_split(char *str, char c);
// char				**pipe_split(char *str, char c);
void				ft_putstr_fd(char *s, int fd);
void				*ft_free(char **str);
void				ft_lstadd_back(t_cmd **head, t_cmd *new);
void				ft_lstadd_back2(t_lexer **head, t_lexer *new);
char				*ft_itoa(int n);
t_lexer				*add_node(char *str);
int					ft_isalpha(int c);;

/* PARSING FUNCTIONS */

void				clear_cmd_list(t_cmd *head);
int					special_char(char c);
int					path_check(char *s);
char				**environment(t_main *main);
char				*return_path(char **ev, char *str);
t_cmd				*create_list(t_cmd *list, t_lexer *lexer, char **ev);
t_lexer				*tokenize(char *str, t_main *main);
void				expand(t_lexer *list, t_main *main);
int					valid_name(char c);
int					heredoc_breakers(char c);
void				fill_node(t_lexer **list, char *result);
void				skip_her(t_lexer **list, char *result);
int					valid_condition(t_lexer *list);
char				*put_value(t_main *main, char *output);
int					special_char(char c);
int					find_dollar(char *str);
int					pipe_syntax(char *str);
int					in_redirections_syntax(char *str);
int					out_redirections_syntax(char *str);
int					next_false(t_lexer *list);
bool				syntax_error(t_lexer *list);
enum				e_type add_type(t_lexer *list);
int					flag(t_lexer *list);
void				give_type(t_lexer *list);
int					count_args(t_lexer *list);
int					count_redir_out(t_lexer *list);
int					count_redir_in(t_lexer *list);
int					count_her(t_lexer *list);
int					count_append(t_lexer *list);
int					valid_syntax_condition(t_lexer *list, int flag);
void				re_lex_2(t_lexer **list);
void				re_lex(t_lexer *list);
void				fill_input_file(t_lexer **lexer, t_cmd *tmp_list);
void				fill_output_file(t_lexer **lexer, t_cmd *tmp_list);
void				fill_append_file(t_lexer **lexer, t_cmd *tmp_list);
void				fill_heredoc(t_lexer **lexer, t_cmd *tmp_list);
void				fill_args(t_lexer **lexer, t_cmd *tmp_list);
void				clear(t_cmd *cmd, char *line);
void				clear_all(t_main **main);
void				clear_lexer_list(t_lexer *head);

/* EXECUTION FUNCTIONS */

void 				child_exec(t_main *main, t_cmd *cmd, int *prev_pipe_fd, int file_count, int *pipe_fd);
void				execute_single_command(t_main *main, t_cmd *cmd);
void            	handle_input_redirection(t_cmd *cmd, t_main *main, int *prev_pipe_fd, int file_count);
void				handle_output_redirection(t_cmd *cmd, int *pipe_fd);
int					check_if_builtin(char *str);
void				execute_command(t_main *main);
void				simple_exec(t_main *main);
void				simple_cleanup(t_cmd *cmd);
void				execute_builtins(t_main *main, t_cmd *cmd);
void				ft_lstadd_back_env(t_env **head, t_env *new);
void				update_env_value(t_env **env, char *name, char *value);
void				print_export(t_main *main);
int					check_export(char **split);
void				handle_heredoc(t_main *main);
int					count_commands(t_cmd *cmd);
char				*her_expand(char *str, t_main *main);
void				handle_signals(void);
t_env				*ft_lstlast_env(t_env *lst);
void				pipe_exec_with_redirection(t_main *main);
void 				error2(t_main *main, char *str, int status);
void				error(char *str);

/* A77 */

int					exec_echo(t_cmd *cmd);
int					excec_pwd(void);
int					exec_env(t_main *main);
int					exec_cd(t_main *main, t_cmd *cmd);
int					exec_exit(t_main *main);
int					exec_export(t_main *main, t_cmd *cmd);
int					exec_unset(t_main *main, t_cmd *cmd);

#endif