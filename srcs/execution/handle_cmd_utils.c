/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brbaazi <brbaazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 09:04:49 by abjellal          #+#    #+#             */
/*   Updated: 2025/08/18 10:03:40 by brbaazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(char *cmd_name, t_env *env_list)
{
	char	**paths;
	char	*path_var;
	char	*full_path;
	char	*checked_path;
	int		i;

	i = -1;
	path_var = get_env_value(env_list, "PATH");
	if (!path_var)
		return (ft_strdup(cmd_name));
	paths = ft_split(path_var, ':');
	if (!paths)
		return (ft_strdup(cmd_name));
	while (paths[++i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = strjoin_free(full_path, cmd_name);
		checked_path = check_full_path(full_path);
		if (checked_path)
			return (checked_path);
	}
	return (NULL);
}

static void	handle_empty_args(t_cmd *cmd)
{
	if (!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
	{
		if (cmd->args && cmd->args[1])
		{
			cmd->args++;
		}
		else
			cleanup_and_exit(0);
	}
}

static char	*get_executable_path(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	if (ft_strchr(cmd->args[0], '/'))
		path = ft_strdup(cmd->args[0]);
	else
		path = get_cmd_path(cmd->args[0], shell->env_list);
	if (!path)
	{
		write_error_msg(cmd->args[0], ": command not found\n");
		cleanup_and_exit(127);
	}
	return (path);
}

static void	validate_path(t_cmd *cmd, char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		write_error_msg(cmd->args[0], ": Is a directory\n");
		cleanup_and_exit(126);
	}
	if (access(path, X_OK) != 0 && errno == EACCES)
	{
		write_error_msg(cmd->args[0], ": Permission denied\n");
		cleanup_and_exit(126);
	}
	if (path[ft_strlen(path) - 1] == '/')
	{
		write_error_msg(cmd->args[0], ": Not a directory\n");
		cleanup_and_exit(126);
	}
}

int	exec_external(t_shell *shell, t_cmd *cmd)
{
	char	**envp;
	char	*path;

	handle_empty_args(cmd);
	envp = env_to_array(shell->env_list);
	path = get_executable_path(shell, cmd);
	validate_path(cmd, path);
	execve(path, cmd->args, envp);
	perror(cmd->args[0]);
	cleanup_and_exit(127);
	return (0);
}
