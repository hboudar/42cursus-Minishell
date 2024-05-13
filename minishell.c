/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:50:46 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/13 16:40:51 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_term(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &term);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	free(cmd);
}

void	print_cmd(t_cmd *cmd)
{
	if (!cmd || cmd->args[0] == NULL)
		printf("Empty command\n");
	else
	{
		int	i;

		i = 0;
		while (cmd->args[i])
		{
			printf("%s", cmd->args[i]);
			i++;
		}
	}
}

void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s" , env->key);
		if (env->value)
			printf("%s\n", env->value);
		else
			printf("\n");
		env = env->next;
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
	while (1)
	{
		line = readline("\033[1;34m➜ minishell \033[0m");
		if (!line)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
			prompt = parse_prompt(line, env);
			printf("execution \n");
			if (prompt && (prompt->type != P_CMD || prompt->cmd))
				execution(prompt, env);
		}
		free(line);
	}
	return (0);
}
