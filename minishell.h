/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:53:04 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/18 12:24:31 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "utils/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <termios.h>
# include <term.h>
# include <limits.h>
# include <stdbool.h>
# include <signal.h>

enum e_prmpt_type
{
	P_CMD,
	P_PIPE,
	P_AND,
	P_OR,
};

enum e_cmd_type
{
	CMD,
	HERE_DOC,
};

//execution
enum e_state
{
	GENERAL,
	ENVIROMENT,
	IN_SQUOTES,
	IN_DQUOTES,
	LIMITER,
};

//parsing
enum e_type
{
	WORD,
	PIPE_TKN,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	WHITE_SPACE,
	ENV,
	REDIR_HERE_DOC,
	SQUOTES,
	DQUOTES,
	OPENPAR,
	CLOSEPAR,
	AND_TOKEN,
	OR_TOKEN,
	SEMI_COLON,
	ERROR,
	WILDCARD
};

enum e_print
{
	PRINT,
	NO_PRINT,
	ENV_PRINT,
	EXP_PRINT,
};

typedef struct s_pid
{
	pid_t			pid;
	struct s_pid	*next;
}				t_pid;

typedef struct s_env
{
	char			*key;
	char			*value;
	enum e_print	print;
	struct s_env	*next;
}	t_env;

typedef struct s_file
{
	int				fd;
	int				type;
	int				quotes;
	char			*data;
	struct s_file	*next;
}	t_file;

typedef struct s_expand
{
	char			*data;
	int				index;
	int				quotes;
	struct s_expand	*next;
}	t_expand;

typedef struct s_data
{
	char			*arg;
	int				joinable;
	enum e_type		type;
	enum e_state	state;
	struct s_data	*next;
}	t_data;

typedef struct s_limiter
{
	char				*limit;
	int					quotes;
	struct s_limiter	*next;
}		t_limiter;

typedef struct s_cmd
{
	char			**args;
	t_data			*data;
	t_file			*file;
	t_expand		*expand;
	t_limiter		*limiter;
	enum e_cmd_type	type;
}		t_cmd;

typedef struct s_prompt
{
	int					subshell;
	int					exit_state;
	t_cmd				*cmd;
	t_file				*file;
	t_limiter			*limiter;
	enum e_prmpt_type	type;
	struct s_prompt		*left;
	struct s_prompt		*right;
}		t_prompt;

typedef struct s_token
{
	int				size;
	int				joinable;
	char			*data;
	char			**expand;
	enum e_type		type;
	enum e_state	state;
	struct s_token	*next;
}		t_token;

int			ft_iswhitespace(char *str);
int			check_and_or(t_token *token);
int			has_pipe(t_token *token);
int			check_syntax(t_token *token);
int			check_syntax_bonus(t_token *token);
int			has_pipe(t_token *token);
int			count_files(char **file);
int			check_env(char **envp);
int			get_args_count(t_data *data);
int			was_syn_err(t_prompt *prompt);
int			check_and_or_limit(t_token *token, t_token *limit);
int			prep_execution(t_prompt *prompt, t_env **env, int mode);
char		*ft_remove_quotes(char *str);
char		**ft_split_expand(char *str);
char		**ft_dupexpand(char **expand);
char		*get_expanded_value(char **data, t_env *env);
void		replace_exit_state(t_prompt *prompt, t_data *data);
void		init_signals(t_prompt *prompt, int mode);
void		remove_arg(t_cmd *cmd, int i, char *to_add);
void		add_and_split(t_cmd *cmd, t_expand *expand, t_env *env);
void		free_token_limit(t_token **token, t_token *limit);
void		expand_cmd(t_prompt *prmpt, t_env *env);
void		handle_sigint(int signum);
void		set_size(t_token *token);
void		expand_wildcard(t_token **token);
void		expand_string(char **str, t_env *env, int expand, char *tmp2);
void		split_expand(t_token *token);
void		fill_expand(t_cmd *cmd, t_token *token);
void		get_expand(char **line, t_token *token);
void		remove_redirections_subshell(t_token **token, t_token *limit);
void		handle_subshells(t_prompt **prmpt, t_token **token, t_token *limit);
void		handle_sigint(int signum);
void		tokenize_whitespace(char **line, int *i, t_token **token);
void		add_last(char ***file, char *data);
void		tokenize_dquotes(char **line, int *i, t_token **token);
void		tokenize_squotes(char **line, int *i, t_token **token);
void		tokenize_pipe(char **line, int *i, t_token **token);
void		get_cmd(t_cmd **cmd, t_token *token);
void		free_tab(char ***args);
void		tokenize_append(char **line, int *i, t_token **token);
void		free_cmd(t_cmd **cmd);
void		split_expanded(t_prompt *prmpt, t_data **data, char *expanded);
void		add_token(t_token *new_token);
void		add_data(t_data **org, t_data **data, char **new_data, int join);
void		fill_redirections(t_cmd *cmd, t_token *token);
void		tokenize_redir_out(char **line, int *i, t_token **token);
void		tokenize_redir_in(char **line, int *i, t_token **token);
void		tokenize_here_doc(char **line, int *i, t_token **token);
void		tokenize_env(char **line, int *i, t_token **token);
void		tokenize_word(char **line, int *i, t_token **token);
void		tokenize_semicolon(char **line, int *i, t_token **token);
void		tokenize_error(char **line, int *i, t_token **token);
void		tokenize_wildcard(char **line, int *i, t_token **token);
void		tokenize(char **line, int *i, t_token **token);
void		fix_token(t_token **token);
void		get_token_state(t_token *token);
void		free_token(t_token **token);
void		get_token_type(t_token *token);
void		get_token_state(t_token *token);
void		remove_token(t_token **token, t_token *node);
void		ft_fileaddback(t_file **file, t_file *new);
void		free_prompt(t_prompt **prompt);
void		free_cmd(t_cmd **cmd);
void		free_files(t_file *file);
void		remove_redirections(t_token **token);
void		fill_redirections_sub(t_prompt *prmpt, t_token *tkn, t_token *lmt);
void		ft_shell_lvl(t_env *env);
void		build_prompt(t_prompt **prmpt, t_token **token);
void		parse_pipes(t_prompt **prmpt, t_token **token);
void		parse_prompt(t_prompt **oldprmpt, char *line);
void		split_token(t_token *token, t_token *split, t_token **res);
void		end_token(t_token **token);
void		get_args(t_cmd *cmd);
void		get_cmd(t_cmd **cmd, t_token *token);
t_env		*ft_tabdup(char **args, int i, int j);
t_cmd		*parse_cmd(t_token	**token);
size_t		ft_tablen(char **args);
t_file		*ft_newfile(char *data, int type, enum e_state state);
t_token		*get_closepar(t_token *token);
t_token		*parse_token(char *line);
t_token		*get_and_or(t_token *token);
t_token		*get_limit(t_token *token);
t_token		*pipeless_token(t_token *token);

void		here_doc(t_prompt *prompt, t_env *env);
int			execution(t_prompt *prompt, t_env **env, t_pid **pids);
int			subshell(t_prompt *prompt, t_env **env, int *fd, t_pid **pids);
int			ft_cmd(t_prompt *prompt, t_env **env, t_pid **pids);
int			none_builtin(t_prompt *prompt, t_env *env, int mode, t_pid **pids);
int			ft_pipe(t_prompt *prompt, t_env **env, char side, t_pid **pids);
int			ft_or(t_prompt *prompt, t_env **env, t_pid **pids);
int			ft_and(t_prompt *prompt, t_env **env, t_pid **pids);

void		redirection(t_prompt *prompt, t_env **env, t_file *file);
void		none_redirection(t_prompt *prompt, t_env *env, t_file *file);
int			ft_echo(t_prompt *prompt, t_env *env);
int			ft_cd(t_prompt *prompt, t_env *env, char *oldpwd, char *pwd);
int			ft_pwd(t_env *env);
int			ft_export(t_prompt *prompt, t_env *env, char *equal, char *plus);
int			export_only(t_env *env);
void		add_env_plus(const char *str, t_env *env);
void		add_env_equal(const char *str, t_env *env);
int			ft_unset(t_prompt *prompt, t_env **env);
int			ft_env(t_prompt *prompt, t_env *env);
int			ft_exit(t_prompt *prompt);

int			error(char *msg);
int			ft_builtin(t_prompt *prompt, t_env **env);
int			is_builtin(t_prompt *prompt);
char		*find_path(char **cmd, t_env *env);
char		**env_to_envp(t_env *env, t_env *env1);
char		**free_envp(char **envp);
void		setup_signal_handlers(void (*int_)(int), void (*quit_)(int));
void		sigint_handler_heredoc(int sig);
void		ignore_signals(void);
void		sig_handler_child(int sig);

int			change_underscore(t_env **env, char *str);
char		*get_env(char *key, t_env *env, int mode);
void		pid_addback(t_pid **pids, t_pid *new);
t_pid		*new_pid(pid_t pid);
void		free_pid(t_pid **pids);

#endif