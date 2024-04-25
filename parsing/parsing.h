/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:26:22 by aoulahra          #+#    #+#             */
/*   Updated: 2024/04/23 15:48:51 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_H
# define PARSING_H
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
# include <curses.h>
# include <limits.h>
# include <stdbool.h>

enum e_prmpt_type
{
	AND,
	OR,
	NONE,
};

enum e_cmd_type
{
	CMD,
	HERE_DOC,
	PIPECMD,
};

enum e_state
{
	IN_SQUOTES,
	IN_DQUOTES,
	GENERAL,
};

enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HERE_DOC,
} t_type;

typedef struct s_cmd
{
	char			**args;
	int				size;
	char			*infile;
	char			*outfile;
	char			*limiter;
	int				appendable;
    enum e_cmd_type	type;
    enum e_state	state;
	struct s_cmd	*left;
	struct s_cmd	*right;
}		t_cmd;

typedef struct s_prompt
{
	t_cmd				*cmd;
	enum e_prmpt_type	type;
	struct s_prompt		*left;
	struct s_prompt		*right;
}		t_prompt;

typedef struct s_token
{
	char			*data;
	int				size;
	enum e_type		type;
	enum e_state	state;
	struct s_token	*next;
}		t_token;

t_prompt	*parse_prompt(char *line);
t_cmd		*parse_line(char *line);
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

#endif
