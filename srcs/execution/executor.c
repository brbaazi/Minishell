/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abjellal <abjellal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:45:18 by brbaazi           #+#    #+#             */
/*   Updated: 2025/08/16 20:30:29 by abjellal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_shell *shell, t_cmd *cmd_list)
{
	int	status;

	if (process_heredocs(cmd_list, shell) == -1)
		return (1);
	status = 0;
	if (cmd_list->pipe_out)
	{
		status = execute_pipeline(shell, cmd_list);
		handle_signals();
	}
	else
		status = handle_cmd(shell, cmd_list);
	shell->exit_status = status;
	return (status);
}
