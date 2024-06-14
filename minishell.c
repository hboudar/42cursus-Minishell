/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 02:38:00 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/14 04:10:46 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_caught = 0;

int	prep_execution(t_prompt *prompt, t_env **env)
{
	int	std_in;
	int	std_out;
	int	exit_state;
	t_pid	*pid;

	std_in = dup(0);
	std_out = dup(1);
	pid = NULL;
	here_doc(prompt, *env);
	if (g_caught != 2)
		exit_state = execution(prompt, env, pid);
	else
		exit_state = 1;
	printf("{exit_state = %d}\n", exit_state);
	dup2(std_in, 0);
	dup2(std_out, 1);
	close(std_in);
	close(std_out);
	return (exit_state);
}

int	end_program(t_prompt *prompt)
{
	if (prompt && prompt->cmd)
	{
		free_cmd(&prompt->cmd);
		prompt->cmd = NULL;
	}
	init_signals(prompt);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env		*env;
	t_prompt	*prompt;

	(void)argv;
	if (!isatty(0) || argc != 1 || check_env(envp))
		exit (1);
	env = ft_tabdup(envp, -1, 0);
	prompt = NULL;
	while (1)
	{
		init_signals(prompt);
		line = readline("\033[1;34m➜ minishell \033[0m");
		if (!line)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
			parse_prompt(&prompt, line);
			if (!was_syn_err(prompt) && (prompt->type != P_CMD || prompt->cmd))
				prompt->exit_state = prep_execution(prompt, &env);
		}
		free(line);
	}
	(end_program(prompt)) && (ft_exit(prompt));
}
