/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:26:22 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/06 16:38:27 by aoulahra         ###   ########.fr       */
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
	PIPE,
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
	PIPE_TOKEN,
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			**args;
	int				size;
	char			*infile;
	char			*outfile;
	int				appendable;
	char			limiter;
	enum e_cmd_type	type;
	enum e_state	state;
	struct s_cmd	*left;
	struct s_cmd	*right;
}		t_cmd;

typedef struct s_prompt
{
	t_cmd				*cmd;
	//exit state to be filled by the execution
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

t_prompt	*parse_prompt(char *line, t_env *env);
t_cmd		*parse_line(char *line, t_env *envp);
t_token		*parse_token(char *line);
void		get_token_type(t_token *token);
void		get_token_state(t_token *token);
char		**ft_split_prompt(char *line, char *sep1, char *sep2);
int			has_pipe(t_token *token);
void		get_cmd(t_cmd **cmd, t_token *token);
void		free_tab(char **args);
size_t		ft_prmptlen(char *line);
size_t		ft_tablen(char **args);
void		free_cmd(t_cmd *cmd);
void		free_token(t_token *token);
void		print_cmd(t_cmd *cmd);
t_env		*ft_tabdup(char **args);
t_token		*pipeless_token(t_token *token);
void		expand_env(t_token *token, t_env *env);
char		*ft_getenv(char *name, t_env *env);
void		set_size(t_token *token);
int			ft_iswhitespace(char *str);
void		tokenize_whitespace(char **line, int *i, t_token **token);
void		tokenize_dquotes(char **line, int *i, t_token **token);
void		tokenize_squotes(char **line, int *i, t_token **token);
void		tokenize_pipe(char **line, int *i, t_token **token);
void		tokenize_append(char **line, int *i, t_token **token);
void		tokenize_redir_out(char **line, int *i, t_token **token);
void		tokenize_redir_in(char **line, int *i, t_token **token);
void		tokenize_here_doc(char **line, int *i, t_token **token);
void		tokenize_env(char **line, int *i, t_token **token);
void		tokenize_word(char **line, int *i, t_token **token);
void		tokenize(char **line, int *i, t_token **token);
int			check_and_or(t_token *token);
t_cmd		*parse_cmd(t_token	*token, t_env *env);
t_token		*get_and_or(t_token *token);
void		free_token(t_token *token);
void		get_token_state(t_token *token);
char		*ft_remove_quotes(char *str);
void		get_token_type(t_token *token);
int			has_pipe(t_token *token);
void		print_tokens(t_token *token);
void		print_prompt(t_prompt *prompt);
void		remove_token(t_token **token, t_token *node);

#endif
