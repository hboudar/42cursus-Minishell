/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:01:04 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/11 19:08:15 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/parsing.h"

//execution main :

void	here_doc(t_prompt *prompt, t_env *env);
int	    execution(t_prompt *prompt, t_env **env, int std_in);
int     subshell(t_prompt *prompt, t_env **env);
int	    ft_cmd(t_prompt *prompt, t_env **env);
int     ft_pipe(t_prompt *prompt, t_env **env, int fd_in);
int	    ft_or(t_prompt *prompt, t_env **env, int fd_in);
int	    ft_and(t_prompt *prompt, t_env **env, int fd_in);

//one_cmd / no_cmd:

int     execute_nonebuiltin(t_prompt *prompt, t_env *env, int mode);
void    redirection(t_prompt *prompt, t_env **env);
int     ft_echo(t_prompt *prompt, t_env *env);
int     ft_cd(t_prompt *prompt, t_env *env);
int     ft_pwd(t_prompt *prompt, t_env *env);
int     ft_export(t_prompt *prompt, t_env *env);
void    add_env_plus(const char *str, t_env *env);
void    add_env_equal(const char *str, t_env *env);
int     ft_unset(t_prompt *prompt, t_env **env);
int     ft_env(t_prompt *prompt, t_env *env);
int     ft_exit(t_prompt *prompt);

//utils :

int     error(char *msg); //error
int     ft_builtin(t_prompt *prompt, t_env **env); //checks if builtin
int     is_builtin(t_prompt *prompt);
char	*find_path(char **cmd, t_env *env); //findning the path of the command
char	**env_to_envp(t_env *env, t_env *env1); //converting the env to envp
char    **free_envp(char **envp); //freeing the envp
void    setup_signal_handlers(void (*int_handler)(int), void (*quit_handler)(int)); //setting up the signal handlers
void    sigint_handler_heredoc(int sig); //signal handler for heredoc
void    ignore_signals(void); //ignoring signals
void    sig_handler_child(int sig); //signal handler for child

int     subshell_redirection(t_prompt *prompt, t_env **env, int *fd);

#endif
