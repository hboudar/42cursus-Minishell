/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:01:04 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/14 05:15:42 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/parsing.h"

typedef struct s_pid
{
    pid_t			pid;
    struct s_pid	*next;
}				t_pid;

void	here_doc(t_prompt *prompt, t_env *env);
int		execution(t_prompt *prompt, t_env **env, t_pid **pids);
int		subshell(t_prompt *prompt, t_env **env, int *fd, t_pid **pids);
int		ft_cmd(t_prompt *prompt, t_env **env);
int		execute_nonebuiltin(t_prompt *prompt, t_env *env, int mode);
int		ft_pipe(t_prompt *prompt, t_env **env, char side, t_pid **pids);
int		ft_or(t_prompt *prompt, t_env **env, t_pid **pids);
int		ft_and(t_prompt *prompt, t_env **env, t_pid **pids);

void	redirection(t_prompt *prompt, t_env **env, t_file *file);
void	non_redirection(t_prompt *prompt, t_env *env, t_file *file);
int		ft_echo(t_prompt *prompt, t_env *env);
int		ft_cd(t_prompt *prompt, t_env *env, char *oldpwd, char *pwd);
int		ft_pwd(t_prompt *prompt, t_env *env);
int		ft_export(t_prompt *prompt, t_env *env);
void	add_env_plus(const char *str, t_env *env);
void	add_env_equal(const char *str, t_env *env);
int		ft_unset(t_prompt *prompt, t_env **env);
int		ft_env(t_prompt *prompt, t_env *env);
int		ft_exit(t_prompt *prompt);

int		error(char *msg);
int		ft_builtin(t_prompt *prompt, t_env **env);
int		is_builtin(t_prompt *prompt);
char	*find_path(char **cmd, t_env *env);
char	**env_to_envp(t_env *env, t_env *env1);
char	**free_envp(char **envp);
void	setup_signal_handlers(void (*int_)(int), void (*quit_)(int));
void	sigint_handler_heredoc(int sig);
void	ignore_signals(void);
void	sig_handler_child(int sig);

void	pid_addback(t_pid **pids, t_pid *new);
t_pid	*new_pid(pid_t pid);

#endif
