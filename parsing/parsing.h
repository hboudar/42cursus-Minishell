/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:26:22 by aoulahra          #+#    #+#             */
/*   Updated: 2024/04/23 13:06:25 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
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
	PARENTHESIS,
	NONE,
};

enum e_type
{
	CMD,
	IN_REDIR,
	OUT_REDIR,
	APPEND_REDIR,
	HERE_DOC,
	PIPE,
};

enum e_state
{
	IN_SQUOTES,
	IN_DQUOTES,
	GENERAL,
};

typedef struct s_cmd
{
	char			*data;
	char			**args;
    enum e_type		type;
    enum e_state	state;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_prompt
{
	t_cmd				*cmd;
	enum e_prmpt_type	type;
	struct s_prompt		*left;
	struct s_prompt		*right;
}		t_prompt;

#endif
