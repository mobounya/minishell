/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:09:02 by mobounya          #+#    #+#             */
/*   Updated: 2020/01/15 19:08:15 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int			ft_run_binary(char *path, char **args, char **env)
{
	int pid;

	if (access(path, F_OK))
		return (1);
	if (access(path, X_OK))
		return (3);
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, args, env) == -1)
			exit(1);
	}
	else
		wait(NULL);
	return (0);
}

char		*ft_get_path(char *path, char *binary)
{
	char	*var_path;
	char	*binary_path;

	var_path = ft_strjoin(path, "/");
	binary_path = ft_strjoin(var_path, binary);
	ft_memdel((void **)&var_path);
	return (binary_path);
}

int			ft_bin_helper(char *var_path, char **tokens, char *cmd, char **env)
{
	int		error;
	char	*bin_path;
	char	**path;
	uint	i;

	error = 1;
	i = 0;
	path = ft_strsplit(var_path, ':');
	ft_memdel((void **)&var_path);
	while (path[i])
	{
		bin_path = ft_get_path(path[i], cmd);
		error = ft_run_binary(bin_path, tokens, env);
		ft_memdel((void **)&bin_path);
		if (error == 0 || error == 3)
			break ;
		i++;
	}
	ft_free_double((void **)path);
	return (error);
}

int			ft_bin_execute(t_argument *arguments)
{
	char	*var_path;
	uint	i;
	int		error;

	i = -1;
	if (arguments->tokens[0][0] == '/' || arguments->tokens[0][0] == '.')
	{
		error = ft_run_binary(arguments->tokens[0], \
		arguments->tokens, arguments->env);
		if (error == 1)
			return (2);
		return (error);
	}
	var_path = ft_search_vr(arguments->env, "PATH");
	error = 1;
	if (var_path)
	{
		error = ft_bin_helper(var_path, arguments->tokens, \
		arguments->tokens[0], arguments->env);
	}
	return (error);
}
