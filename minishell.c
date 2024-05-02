/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:50:46 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/01 18:49:02 by aoulahra         ###   ########.fr       */
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
	if (cmd && cmd->type == PIPECMD)
	{
		print_cmd(cmd->left);
		printf("|");
		print_cmd(cmd->right);
	}
	else if (!cmd || cmd->args[0] == NULL)
		printf("Empty command\n");
	else
	{
		int	i;

		i = 0;
		while (cmd->args[i])
		{
			printf(" %s", cmd->args[i]);
			i++;
		}
	}
}

void	print_prompt(t_prompt *prompt)
{
	if (prompt->type == AND)
	{
		print_prompt(prompt->left);
		printf("&&");
		print_prompt(prompt->right);
	}
	else if (prompt->type == OR)
	{
		print_prompt(prompt->left);
		printf("||");
		print_prompt(prompt->right);
	}
	else
		print_cmd(prompt->cmd);
}

void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env		*env;
	t_prompt	*prompt;

	(void)argc;
	(void)argv;
	init_term();
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
			print_prompt(prompt);
			printf("\n");
		}
		free(line);
	}
	return (0);
}
