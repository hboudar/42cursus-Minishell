/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:04 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/18 12:18:06 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_path(char *path, char *key, t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(env->key)))
		{
			free(env->key);
			env->key = ft_strdup(key);
			(env->value) && (free(env->value), env->value = NULL);
			env->value = ft_strdup(path);
			env->print = PRINT;
			break ;
		}
		env = env->next;
	}
	free(path);
}

char	*ft_getpath(char *arg, t_env *env, int mode)
{
	char	*pwd;
	char	*tmp;

	(1) && (pwd = NULL, tmp = NULL);
	pwd = getcwd(NULL, 0);
	while (!pwd && env)
	{
		if (!ft_strncmp(env->key, "PWD=", 5))
		{
			if (!mode)
				pwd = ft_strdup(env->value);
			else
			{
				tmp = ft_strjoin(env->value, "/");
				pwd = ft_strjoin(tmp, arg);
				free(tmp);
			}
			break ;
		}
		env = env->next;
	}
	if (!pwd && !env)
		return (NULL);
	return (pwd);
}

int	tohome_wego(t_env *env)
{
	char	*home;
	char	*oldpwd;
	char	*pwd;

	(1) && (home = NULL, oldpwd = NULL, pwd = NULL);
	home = get_env("HOME=", env, 0);
	oldpwd = ft_getpath(NULL, env, 0);
	if (chdir(home) == -1)
	{
		(home) && (free(home), home = NULL);
		(oldpwd) && (free(oldpwd), oldpwd = NULL);
		perror("Error in chdir");
		return (1);
	}
	pwd = ft_getpath(NULL, env, 0);
	set_path(pwd, "PATH=", env);
	set_path(oldpwd, "OLDPWD=", env);
	(home) && (free(home), home = NULL);
	return (0);
}

int	ft_cd(t_prompt *prompt, t_env *env, char *oldpwd, char *pwd)
{
	if (prompt->cmd->args[1] == NULL)
		return (tohome_wego(env));
	oldpwd = ft_getpath(prompt->cmd->args[1], env, 0);
	if (chdir(prompt->cmd->args[1]) == -1)
	{
		(oldpwd) && (free(oldpwd), oldpwd = NULL);
		perror("Error in chdir");
		return (1);
	}
	pwd = ft_getpath(prompt->cmd->args[1], env, 1);
	set_path(pwd, "PWD=", env);
	set_path(oldpwd, "OLDPWD=", env);
	return (0);
}
