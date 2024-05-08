/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:01:04 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/08 10:27:00 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/parsing.h"

//execution main :

int execution(t_prompt *prompt, t_env *env);

//builtins :

int is_builtin(t_prompt *prompt);
int execute_builtin(t_prompt *prompt, t_env *env);
int ft_echo(t_prompt *prompt, t_env *env);
int ft_cd(t_prompt *prompt, t_env *env);
int ft_pwd(t_prompt *prompt);
int ft_export(t_prompt *prompt, t_env *env);
int ft_unset(t_prompt *prompt, t_env *env);
int ft_env(t_prompt *prompt, t_env *env);
int ft_exit(t_prompt *prompt);

//non builtins :

int    execute_nonebuiltin(t_prompt *prompt, t_env *env);

//utils :

char	*find_path(char **cmd, t_env *env);
char	**env_to_envp(t_env *env);
char   **free_envp(char **envp);

#endif
