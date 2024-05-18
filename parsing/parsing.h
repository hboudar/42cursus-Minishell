/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:26:22 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/18 18:24:03 by aoulahra         ###   ########.fr       */
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
	INFILE,
	OUTFILE,
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
	char			*data;
	int				type;
	int				appendable;
	struct s_file	*next;
}	t_file;

typedef struct s_cmd
{
	char			**args;
	int				size;
	t_file			*file;
	char			**limiter;
	enum e_cmd_type	type;
}		t_cmd;

typedef struct s_prompt
{
	t_cmd				*cmd;
	int					exit_state;
	enum e_prmpt_type	type;
	struct s_prompt		*left;
	struct s_prompt		*right;
}		t_prompt;

typedef struct s_token
{
	char			*data;
	int				size;
	int				skip_space;
	enum e_type		type;
	enum e_state	state;
	struct s_token	*next;
}		t_token;

int			ft_iswhitespace(char *str);
int			check_and_or_pipe(t_token *token);
int			has_pipe(t_token *token);
int			check_syntax(t_token *token);
int			check_syntax_bonus(t_token *token);
int			has_pipe(t_token *token);
int			has_semicolon(char *line);
int			count_files(char **file);
int			was_syntax_error(t_prompt *prompt);
char		*ft_getenv(char *name, t_env *env);
char		*ft_remove_quotes(char *str);
void		set_size(t_token *token);
void		tokenize_whitespace(char **line, int *i, t_token **token);
void		add_last(char ***file, char *data);
void		tokenize_dquotes(char **line, int *i, t_token **token);
void		expand_env(t_token *token, t_env *env);
void		tokenize_squotes(char **line, int *i, t_token **token);
void		tokenize_pipe(char **line, int *i, t_token **token);
void		get_cmd(t_cmd **cmd, t_token *token);
void		free_tab(char **args);
void		tokenize_append(char **line, int *i, t_token **token);
void		free_cmd(t_cmd **cmd);
void		free_token(t_token *token);
void		print_cmd(t_cmd *cmd);
void		fill_redirections(t_cmd *cmd, t_token *token);
void		tokenize_redir_out(char **line, int *i, t_token **token);
void		tokenize_redir_in(char **line, int *i, t_token **token);
void		tokenize_here_doc(char **line, int *i, t_token **token);
void		tokenize_env(char **line, int *i, t_token **token);
void		tokenize_word(char **line, int *i, t_token **token);
void		tokenize(char **line, int *i, t_token **token);
void		fix_token(t_token **token);
void		get_token_state(t_token *token);
void		free_token(t_token *token);
void		get_token_type(t_token *token);
void		print_prompt(t_prompt *prompt);
void		print_tokens(t_token *token);
void		get_token_type(t_token *token);
void		get_token_state(t_token *token);
void		remove_token(t_token **token, t_token *node);
void		ft_fileaddback(t_file **file, t_file *new);
void		free_prompt(t_prompt **prompt);
void		free_files(t_file *file);
void		remove_redirections(t_token **token);
void		print_env(t_env *env);
void		print_cmd(t_cmd *cmd);
void		ft_shell_lvl(t_env *env);
void		end_token(t_token *tmp, t_token *token);
void		parse_prompt(t_prompt **oldprmpt , char *line, t_env *env);
t_env		*ft_tabdup(char **args);
t_cmd		*parse_cmd(t_token	*token, t_env *env);
size_t		ft_tablen(char **args);
t_file		*ft_newfile(char *data, int type);
t_token		*parse_token(char *line);
t_token		*pipeless_token(t_token *token);
t_token		*get_and_or_pipe(t_token *token);
t_token		**split_token(t_token *token, t_token *split);

#endif
