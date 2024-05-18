/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:50:46 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/18 18:41:51 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_clear_history();
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
}

void	free_cmd(t_cmd **cmd)
{
	int	i;

	i = 0;
	if (!*cmd)
		return ;
	free_tab((*cmd)->args);
	free_tab((*cmd)->limiter);
	free_files((*cmd)->file);
	(*cmd)->args = NULL;
	(*cmd)->limiter = NULL;
	(*cmd)->file = NULL;	
	free(*cmd);
	*cmd = NULL;
}

void	ft_shell_lvl(t_env *env)
{
	t_env *tmp;
	char *str;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "SHLVL", 5))
		{
			str = ft_itoa(ft_atoi(tmp->value) + 1);
			if (!str)
				return (perror("E: ft_itoa in ft_shell_lvl"));
			if (ft_strncmp(tmp->value, "999", 3) == 0)
			{
				free(str);
				free(tmp->value);
				return ;
			}
			free(tmp->value);
			tmp->value = str;
			break ;
		}
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env		*env;
	t_prompt	*prompt;

	(void)argv;
	if (!isatty(0) || argc != 1 || !envp)
		return (0);
	env = ft_tabdup(envp);
	init_signals();
	prompt = NULL;
	while (1)
	{
		printf("\nexecution\n");
		line = readline("\033[1;34m➜ minishell \033[0m");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (line[0] != '\0')
		{
			add_history(line);
			parse_prompt(&prompt, line, env);
			if (!was_syntax_error(prompt) && (prompt->type != P_CMD || prompt->cmd))
				prompt->exit_state = execution(prompt, &env);
		}
		free(line);
	}
	return (0);
}
