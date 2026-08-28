/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brbaazi <brbaazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:39:57 by abjellal          #+#    #+#             */
/*   Updated: 2025/08/17 22:56:04 by brbaazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell_exec_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmd_list;

	if (line && *line)
		add_history(line);
	tokens = lexer(line, shell);
	cmd_list = parser(tokens, shell);
	if (cmd_list)
	{
		expander(cmd_list, shell);
		executor(shell, cmd_list);
		signal_flag(0);
	}
	else if (tokens)
	{
		shell->exit_status = 2;
	}
}

void	minishell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		signal_flag(0);
		handle_signals();
		input = readline("minishell> ");
		if (!input)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		minishell_exec_line(input, shell);
		free (input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.env_list = init_env_list(envp);
	shell.exit_status = 0;
	get_shell_pointer(&shell);
	minishell_loop(&shell);
	cleanup_function();
	return (shell.exit_status);
}
