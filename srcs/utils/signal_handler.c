/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:42:56 by abjellal          #+#    #+#             */
/*   Updated: 2025/08/16 21:16:54 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_function(void)
{
	clear_history();
	gc_malloc(0, 0);
}

t_shell	*get_shell_pointer(t_shell *ptr)
{
	static t_shell	*value;

	if (ptr != NULL)
		value = ptr;
	return (value);
}

int	signal_flag(int flag)
{
	static int	data;

	if (flag != -1)
		data = flag;
	return (data);
}

void	handler(int sig)
{
	int	current_flag;

	(void)sig;
	current_flag = signal_flag(-1);
	if (current_flag == 0)
	{
		get_shell_pointer(NULL)->exit_status = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (current_flag == 1)
	{
		write(1, "\n", 1);
		cleanup_function();
		exit(130);
	}
}

void	handle_signals(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
