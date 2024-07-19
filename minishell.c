/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 07:49:04 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/19 17:05:58 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_caught = 0;

void	update_exit_state(t_prompt *prompt)
{
	if (prompt->exit_state == 2)
		prompt->exit_state = 130;
	else if (prompt->exit_state > 255)
		prompt->exit_state = prompt->exit_state >> 8;
	if (prompt->exit_state == 3)
		prompt->exit_state = 131;
}

int	prep_execution(t_prompt *prompt, t_env **env, int mode)
{
	int		std_in;
	int		std_out;
	t_pid	*pid;
	t_pid	*tmp;

	(1) && (std_in = dup(0), std_out = dup(1), pid = NULL);
	if (!mode)
		here_doc(prompt, *env);
	if (g_caught != 2)
		prompt->exit_state = execution(prompt, env, &pid);
	else
		prompt->exit_state = 1;
	tmp = pid;
	(1) && (dup2(std_in, 0), dup2(std_out, 1), close(std_in), close(std_out));
	while (pid)
	{
		waitpid(pid->pid, &prompt->exit_state, 0);
		pid = pid->next;
	}
	update_exit_state(prompt);
	free_pid(&tmp);
	return (prompt->exit_state);
}

int	end_program(t_prompt *prompt)
{
	if (prompt && prompt->cmd)
	{
		free_cmd(&prompt->cmd);
		prompt->cmd = NULL;
	}
	init_signals(prompt, 1);
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
		init_signals(prompt, 0);
		line = readline("\033[1;34m➜ minishell \033[0m");
		if (!line)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
			parse_prompt(&prompt, line);
			if (!was_syn_err(prompt) && (prompt->type != P_CMD || prompt->cmd))
				prompt->exit_state = prep_execution(prompt, &env, 0);
		}
		free(line);
	}
	(end_program(prompt)) && (ft_exit(prompt));
}
