/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:01:04 by hboudar           #+#    #+#             */
/*   Updated: 2024/04/30 19:23:34 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/parsing.h"
# include "utils/libft.h"
# include <stdbool.h>


typedef struct s_env
{
    char	*key;
    char	*value;
    struct s_env	*next;
}	t_env;

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


#endif
