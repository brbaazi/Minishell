/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:06:28 by abjellal          #+#    #+#             */
/*   Updated: 2025/08/18 11:19:30 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define REDIR_IN 1
# define REDIR_OUT 2

/* STRUCTURES */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_IN,
	TOKEN_ERROR,
	TOKEN_HEREDOC,
	TOKEN_APPEND
}						t_token_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

typedef struct s_redirect
{
	char				*file;
	int					type;
	int					heredoc_fd;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_cmd
{
	char				**args;
	t_redirect			*redirs;
	int					pipe_out;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_shell
{
	t_env				*env_list;
	int					exit_status;
	int					expand_in_herdoc;

}						t_shell;

typedef struct s_str_list
{
	char				*str;
	struct s_str_list	*next;
}						t_str_list;

typedef struct s_expand_state
{
	t_str_list			**list;
	char				*p;
	char				*segment_start;
	int					in_s_quotes;
	int					in_d_quotes;
	t_shell				*shell;
}						t_expand_state;

/* ========== FUNCTION PROTOTYPES ========== */

/* ---------- Parsing ---------- */

/* Lexer */

t_token					*lexer(char *input, t_shell *shell);
int						is_white_space(char c);
void					skip_white_spaces(char **str);
int						is_quote(char c);
char					*extract_quoted_string(char **input, t_shell *shell);
t_token					*handle_operator(char **input, t_token *tokens);
t_token					*handle_word(char **input, t_token *tokens);
int						handle_operator_token(char **input, t_token **list);
int						is_operator(char c);
char					*extract_word(char **str);
char					*extract_operator(char **str);
int						get_operator_type(char *op);
void					add_token(t_token **token_list, char *value,
							t_token_type type);

/* Parser */
t_cmd					*parser(t_token *tokens, t_shell *shell);
t_cmd					*new_command(void);
void					cmd_add_back(t_cmd **cmd_list, t_cmd *new_cmd);
int						is_pipe(t_token *token);
int						is_redirect(t_token *token);
int						handle_pipe(t_token **tokens, t_cmd **cmd_list,
							t_cmd **current);
int						handle_redirect(t_token **tokens, t_cmd **cmd_list,
							t_cmd *current);
void					add_arg(t_cmd *cmd, char *arg);
int						add_redirect(t_cmd *cmd, int type, char *file);
void					print_syntax_error(char *token);
char					*get_var_value(char **str_ptr, t_shell *shell);
void					append_str_node(t_str_list **list, char *str);
char					*join_str_list(t_str_list *list);
int						process_separator(t_token *tok, t_cmd **list,
							t_cmd **curr);
int						process_single_token(t_token **tokens, t_cmd **cmd_list,
							t_cmd **current_cmd, int *expect_cmd);
int						is_variable_assignment(char *str);
int						process_token_loop(t_token **tokens, t_cmd **cmd_list,
							t_cmd **current_cmd, int *expect_cmd);
int						is_separator(t_token *token);

/*           Execution         */
void					write_error_msg(char *cmd, char *suffix);
int						executor(t_shell *shell, t_cmd *cmd_list);
int						handle_cmd(t_shell *shell, t_cmd *cmd);
int						is_builtin(t_cmd *cmd);
int						exec_builtin(t_shell *shell, t_cmd *cmd, int flag);
int						exec_external(t_shell *shell, t_cmd *cmd);
int						execute_pipeline(t_shell *shell, t_cmd *cmd);
int						check_redirections(t_cmd *cmd);
int						fork_and_execute(t_shell *shell, t_cmd *cmd,
							pid_t *pids, int *in_fd);
void					wait_all_children(pid_t *pids, int cmd_count,
							int *status, int *appeared);
void					parent_close_fds(t_cmd *cmd, int pipe_fd[2],
							int *in_fd);
void					exec_child(t_shell *shell, t_cmd *cmd);
int						create_pipe(int pipe_fd[2]);
pid_t					fork_process(void);
char					*check_full_path(char *full_path);
void					setup_child_process(t_shell *shell, t_cmd *cmd,
							int pipe_fd[2], int in_fd);
int						count_commands(t_cmd *cmd);

/*          Builtins          */
int						check_trailing_spaces(const char *str, int i);
int						skip_spaces_and_sign(const char *str, int *sign);
void					cleanup_function(void);
void					cleanup_and_exit(int exit_code);
int						ft_echo(t_cmd *cmd);
int						cd_builtin(t_shell *shell, t_cmd *cmd);
int						ft_env(t_env *env);
int						ft_export(t_shell *shell, t_cmd *cmd);
int						ft_unset(t_shell *shell, t_cmd *cmd);
int						mini_exit(t_shell *shell, t_cmd *cmd, int flag);
int						ft_pwd(void);
// int			is_numeric(const char *str);
int						check_sign_and_index(const char *str, int *sign);
// int			check_negative_overflow(long long result, char c);
int						check_overflow(const char *str);
int						is_valid_long_long(const char *str);
int						print_and_return(t_env *env_list);
int						wait_and_update_exit_status(pid_t pid, t_shell *shell);

/*          export utils      */

void					split_key_value(char *arg, char **key, char **value);
void					print_exported_env(t_env *env_list);
int						is_valid_identifier(char *key);
int						handle_invalid_key(char *key, t_shell *shell);

/*          Expander       */

void					expander(t_cmd *cmds, t_shell *shell);
char					*expand_heredoc_line(char *line, t_shell *shell);
int						is_expandable(char c);
void					process_quote(t_expand_state *state);
void					process_dollar(t_expand_state *state);
void					init_expand_state(t_expand_state *st, char *arg,
							t_shell *sh);
char					*expand_and_join(char *arg, t_shell *shell);
void					expand_redirs(t_cmd *cmd, t_shell *shell);
void					expand_args(t_cmd *cmd, t_shell *shell);
void					expnd(t_shell *shell, char *line, int write_fd);

/*          Environment      */

t_env					*init_env_list(char **envp);
char					*get_env_value(t_env *env, char *key);
int						set_env_value(t_env *env, char *key, char *value);
void					add_env(t_env **env_list, char *key, char *value);
t_env					*get_env_node(t_env *env_list, char *key);
int						fill_envp_entry(char **envp, int i, t_env *node);
void					ft_free_env_list(t_env *env);
char					**env_to_array(t_env *env_list);

/*          Utils         */

void					free_tokens(t_token *tokens);
void					free_cmds(t_cmd *cmds);
void					free_cmd(t_cmd *cmd);
void					free_redirect(t_redirect *redir);
char					*ft_strndup(const char *s, size_t n);
char					*strjoin_free(char *s1, char *s2);
void					*gc_malloc(size_t size, int mode);
void					print_error(char *prefix, char *target, char *message);
void					free_str_array(char **array);

/*          Signals        */

int						signal_flag(int flag);
void					handle_signals(void);
t_shell					*get_shell_pointer(t_shell *ptr);

/*          libft utils       */

void					ft_lstclear(t_list **lst, void (*del)(void *));
int						ft_lstsize(t_list *lst);
t_list					*ft_lstnew(void *content);
void					ft_lstadd_back(t_list **lst, t_list *new);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strdup(const char *s);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
void					ft_putstr_fd(char *s, int fd);

/*          heredoc       */

int						read_heredoc_input(t_redirect *redir, t_shell *shell);
int						process_heredocs(t_cmd *cmd_list, t_shell *shell);
void					heredoc_loop(t_redirect *redir, t_shell *shell,
							int write_fd);
int						heredoc_parent_process(pid_t pid, t_shell *shell,
							int pipefd[2]);
void					heredoc_child_process(t_redirect *redir, t_shell *shell,
							int pipefd[2]);
char					*remove_soh(char *str);

#endif