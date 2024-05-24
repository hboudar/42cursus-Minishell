/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:50:46 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/24 16:15:35 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_caught = 0;

void	handle_sigint(int signum)
{
	printf("g_caught = %d\n", g_caught);
	if (signum == SIGINT)
	{
		g_caught = 1;
		printf("dkhel\n");
		rl_clear_history();
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	if (g_caught == 0)
	{
		rl_catch_signals = 0;
		signal(SIGINT, &handle_sigint);
		// signal(SIGQUIT, &handle_sigquit);
	}
	else
		g_caught = 0;
}

int	check_env(char **envp)
{
	if (envp && !envp[0])
	{
		printf("Error: empty enviroment\n");
		return (1);
	}
	return (0);
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
	if (!isatty(0) || argc != 1 || check_env(envp))
		exit (1);
	env = ft_tabdup(envp);
	prompt = NULL;
	while (1)
	{
		init_signals();
		line = readline("\033[1;34m➜ minishell \033[0m");
		if (!line)
			break ;
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
