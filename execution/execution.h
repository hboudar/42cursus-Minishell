/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:01:04 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/26 18:38:29 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/parsing.h"

//error :

int error(char *msg);

//execution main :

int execution(t_prompt *prompt, t_env **env);

//one_cmd :

void    here_doc(t_prompt *prompt, int i, int *fd);
int     no_cmd(t_prompt *prompt);
int     is_builtin(t_prompt *prompt);
int     execute_builtin(t_prompt *prompt, t_env **env);
int     ft_echo(t_prompt *prompt, t_env *env);
int     ft_cd(t_prompt *prompt, t_env *env);
int     ft_pwd(t_prompt *prompt, t_env *env);
int     ft_export(t_prompt *prompt, t_env *env);
void    add_env_equal(const char *str, t_env *env);
void    add_env_plus(const char *str, t_env *env);
int     ft_unset(t_prompt *prompt, t_env **env);
int     ft_env(t_prompt *prompt, t_env *env);
int     ft_exit(t_prompt *prompt);
int     execute_nonebuiltin(t_prompt *prompt, t_env *env);


//utils :

int     ft_builtin(t_prompt *prompt, t_env **env);
char	*find_path(char **cmd, t_env *env); //findning the path of the command
char	**env_to_envp(t_env *env, t_env *env1); //converting the env to envp
char   **free_envp(char **envp); //freeing the envp
void    setup_signal_handlers(void (*int_handler)(int), void (*quit_handler)(int)); //setting up the signal handlers
void    sigint_handler_heredoc(int sig); //signal handler for heredoc
void    ignore_signals(void);
void    sig_handler_child(int sig);
#endif
