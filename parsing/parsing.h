/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:26:22 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/09 16:35:02 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../utils/libft.h"
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
# include <curses.h>
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
	ERROR
};

enum e_print
{
	PRINT,
	NO_PRINT,
	ENV_PRINT,
	EXP_PRINT,
};

typedef struct s_env
{
	char			*key;
	char			*value;
	enum e_print	print;
	struct s_env	*next;
}	t_env;

typedef struct s_file
{
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

typedef struct s_cmd
{
	char			**args;
	char			**limiter;
	t_data			*data;
	t_file			*file;
	t_expand		*expand;
	enum e_cmd_type	type;
}		t_cmd;

typedef struct s_prompt
{
	int					subshell;
	int					exit_state;
	char				**limiter;
	t_cmd				*cmd;
	t_file				*file;
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
int			was_syntax_error(t_prompt *prompt);
int			check_and_or_limit(t_token *token, t_token *limit);
int			remove_data(t_prompt *prmpt, t_data **data, int join);
char		*ft_remove_quotes(char *str);
char		*get_expanded_value(char **data, t_env *env);
char		**ft_split_expand(char *str);
void		print_redirections(t_cmd *cmd);
void		replace_exit_state(t_prompt *prompt, t_data *data);
void		init_signals(t_prompt *prompt);
void		remove_arg(t_cmd *cmd, int i, char *to_add);
void		add_and_split(t_cmd *cmd, t_expand *expand, t_env *env);
void		free_token_limit(t_token **token, t_token *limit);
void		expand_cmd(t_prompt *prmpt, t_env *env);
void		handle_sigint(int signum);
void		set_size(t_token *token);
void		split_expand(t_token *token);
void		fill_expand(t_cmd *cmd, t_token *token);
void		get_expand(char **line, t_token *token);
void		remove_redirections_subshell(t_token **token);
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
void		print_cmd(t_cmd *cmd);
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
void		tokenize(char **line, int *i, t_token **token);
void		fix_token(t_token **token);
void		get_token_state(t_token *token);
void		free_token(t_token **token);
void		get_token_type(t_token *token);
void		print_prompt(t_prompt *prompt);
void		print_tokens(t_token *token);
void		get_token_type(t_token *token);
void		get_token_state(t_token *token);
void		remove_token(t_token **token, t_token *node);
void		ft_fileaddback(t_file **file, t_file *new);
void		free_prompt(t_prompt **prompt);
void		free_cmd(t_cmd **cmd);
void		free_files(t_file *file);
void		remove_redirections(t_token **token);
void		fill_redirections_subshell(t_prompt *prmpt, t_token *token);
void		print_env(t_env *env);
void		print_cmd(t_cmd *cmd);
void		ft_shell_lvl(t_env *env);
void		ft_shell_lvl(t_env *env);
void		print_files(t_file *file);
void		build_prompt(t_prompt **prmpt, t_token **token);
void		parse_pipes(t_prompt **prmpt, t_token **token);
void		parse_prompt(t_prompt **oldprmpt, char *line);
char		**ft_dupexpand(char **expand);
void		split_token(t_token *token, t_token *split, t_token **res);
void		end_token(t_token **token);
void		print_expand(t_expand *expand);
void		print_expand_token(t_token *token);
void		get_args(t_cmd *cmd);
void		get_cmd(t_cmd **cmd, t_token *token);
t_env		*ft_tabdup(char **args);
t_cmd		*parse_cmd(t_token	**token);
size_t		ft_tablen(char **args);
t_file		*ft_newfile(char *data, int type, enum e_state state);
t_token		*get_closepar(t_token *token);
t_token		*parse_token(char *line);
t_token		*pipeless_token(t_token *token);
t_token		*get_and_or(t_token *token);

#endif
