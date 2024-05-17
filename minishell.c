/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:50:46 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/16 10:37:21 by aoulahra         ###   ########.fr       */
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
	free_tab(cmd->args);
	free_tab(cmd->limiter);
	free_files(cmd->file);
	cmd->args = NULL;
	cmd->limiter = NULL;
	cmd->file = NULL;	
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

void ft_shell_lvl(t_env *env)
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
	ft_shell_lvl(env);
	prompt = NULL;
	while (1)
	{
		line = readline("\033[1;34m➜ minishell \033[0m");
		if (!line)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
			prompt = parse_prompt(prompt, line, env);
			if (prompt && (prompt->type != P_CMD || prompt->cmd))
				prompt->exit_state = execution(prompt, env);
		}
		free(line);
	}
	return (0);
}
