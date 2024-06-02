/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:50:46 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/25 13:08:49 by aoulahra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_caught = 0;

int	prep_execution(t_prompt *prompt, t_env **env)
{
	// int	std_in;
	// int	std_out;
	int	exit_state;

	// std_in = dup(0);
	// std_out = dup(1);
	// expand_cmd(prompt->cmd, *env); call this function to expand
	exit_state = execution(prompt, env);
	// exit_state = execution(prompt, env, std_in, std_out);
	// dup2(std_in, 0);
	// dup2(std_out, 1);
	// close(std_in);
	// close(std_out);
	return (exit_state);
}

int	end_program(t_prompt *prompt)
{
	if (prompt && prompt->cmd)
	{
		free_cmd(&prompt->cmd);
		prompt->cmd = NULL;
	}
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
			parse_prompt(&prompt, line);
			if (!was_syntax_error(prompt) && (prompt->type != P_CMD || prompt->cmd))
				prompt->exit_state = prep_execution(prompt, &env);
		}
		free(line);
	}
	(end_program(prompt)) && (ft_exit(prompt));
}
