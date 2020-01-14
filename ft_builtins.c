/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 21:14:02 by mobounya          #+#    #+#             */
/*   Updated: 2020/01/14 23:16:01 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int			ft_exit(t_argument *arguments)
{
	uint	i;
	int		status;

	i = 0;
	status = 0;
	while (arguments->tokens[i])
		i++;
	if (i > 2)
	{
		g_errno = 2;
		return (-1);
	}
	else if (arguments->tokens[1])
		status = ft_atoi(arguments->tokens[1]);
	ft_free_double((void **)arguments->tokens);
	ft_free_double((void **)arguments->env);
	ft_memdel((void **)&arguments);
	exit(status);
	return (0);
}

int			ft_echo(t_argument *arguments)
{
	int		i;
	int		line;

	i = 1;
	line = 1;
	while (arguments->tokens[i] && arguments->tokens[i][0] == '-' && \
		arguments->tokens[i][1] != '-')
	{
		if (!ft_strcmp(arguments->tokens[i], "-n"))
			line = 0;
		i++;
	}
	while (arguments->tokens[i])
	{
		ft_putstr(arguments->tokens[i]);
		if (arguments->tokens[i + 1])
			ft_putchar(' ');
		i++;
	}
	(line) ? ft_putchar('\n') : ft_putstr("\e[100m%\e[0m\n");
	return (0);
}

int			ft_changedir(t_argument *arguments)
{
	char *path;

	if (ft_count_arr((void **)arguments->tokens) == 1)
		path = ft_search_vr(arguments->env, "HOME");
	else if (ft_count_arr((void **)arguments->tokens) > 2)
	{
		g_errno = 2;
		return (g_errno);
	}
	else
		path = ft_strdup(arguments->tokens[1]);
	if (path)
	{
		if (access(path, F_OK) != 0)
			g_errno = 1;
		else if (access(path, X_OK) != 0)
			g_errno = 3;
		else
			chdir(path);
		free(path);
		return (g_errno);
	}
	return (0);
}

int			ft_setenv(t_argument *arguments)
{
	uint i;
	char **tmp;

	i = 0;
	if (ft_count_arr((void **)arguments->tokens) > 2)
	{
		g_errno = 2;
		return (-1);
	}
	else if (ft_count_arr((void **)arguments->tokens) == 1 ||
		!ft_strchr(arguments->tokens[1], '='))
	{
		ft_putendl("Usage: setenv VARIABLE=VALUE");
		return (0);
	}
	else if (ft_replace_env(arguments))
	{
		tmp = ft_arpush(arguments->env, ft_strdup(arguments->tokens[1]));
		ft_free_double((void **)arguments->env);
		arguments->env = tmp;
	}
	return (0);
}

int			ft_unsetenv(t_argument *arguments)
{
	uint i;
	uint j;
	char **new;

	i = 0;
	j = 0;
	if (arguments->tokens[1] == NULL)
	{
		ft_putendl("Usage: unsetenv VARNAME");
		return (0);
	}
	if (!(new = malloc(sizeof(char *) *
		ft_count_arr((void **)arguments->env) + 1)))
		return (2);
	while (arguments->env[i])
	{
		if (ft_compare_env(arguments->env[i], arguments->tokens[1]) == 0)
			new[j++] = ft_strdup(arguments->env[i]);
		i++;
	}
	new[j] = NULL;
	ft_free_double((void **)arguments->env);
	arguments->env = new;
	return (0);
}
