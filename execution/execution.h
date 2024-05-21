/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:01:04 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/20 18:35:21 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/parsing.h"

//execution main :

int execution(t_prompt *prompt, t_env **env);

//one_cmd :

int    no_cmd(t_prompt *prompt);

int     is_builtin(t_prompt *prompt);
int     execute_builtin(t_prompt *prompt, t_env **env);
int     ft_echo(t_prompt *prompt, t_env *env);
int     ft_cd(t_prompt *prompt, t_env *env);
int     ft_pwd(t_prompt *prompt);
int     ft_export(t_prompt *prompt, t_env *env);
void    add_env_equal(const char *str, t_env *env);
void    add_env_plus(const char *str, t_env *env);
int     ft_unset(t_prompt *prompt, t_env **env);
int     ft_env(t_prompt *prompt, t_env *env);
int     ft_exit(t_prompt *prompt);

int    execute_nonebuiltin(t_prompt *prompt, t_env *env);


//utils :

char	*find_path(char **cmd, t_env *env);
char	**env_to_envp(t_env *env, t_env *env1);
char   **free_envp(char **envp);
void    signal_handler(int sig);


#endif
