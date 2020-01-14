/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 22:50:44 by mobounya          #+#    #+#             */
/*   Updated: 2020/01/14 23:05:58 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

const t_builtin_matcher g_builtin_tab[6] =
{
	{.name = "exit", .function = &ft_exit},
	{.name = "echo", .function = &ft_echo},
	{.name = "cd", .function = &ft_changedir},
	{.name = "setenv", .function = &ft_setenv},
	{.name = "unsetenv", .function = &ft_unsetenv},
	{.name = "env", .function = &ft_env},
};

int			is_builtin(t_argument *arguments)
{
	uint i;

	g_errno = 0;
	i = 0;
	while (i < 6)
	{
		if (!ft_strcmp(g_builtin_tab[i].name, arguments->tokens[0]))
		{
			if (g_builtin_tab[i].function(arguments))
				ft_errors(g_builtin_tab[i].name);
			return (0);
		}
		i++;
	}
	return (1);
}

int			ft_run_binary(char *path, char **args, char **env)
{
	int pid;

	if (!access(path, F_OK) && !access(path, X_OK))
	{
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
	return (1);
}

int			ft_bin_execute(t_argument *arguments)
{
	char *var_path;
	char **path;
	char *bin;
	uint i;

	i = 0;
	var_path = ft_search_vr(arguments->env, "PATH");
	path = ft_strsplit(var_path, ':');
	ft_memdel((void **)&var_path);
	while (path[i])
	{
		var_path = ft_strjoin(path[i], "/");
		bin = ft_strjoin(var_path, arguments->tokens[0]);
		ft_memdel((void **)&var_path);
		if (ft_run_binary(bin, arguments->tokens, arguments->env) == 0)
		{
			ft_memdel((void **)&bin);
			ft_free_double((void **)path);
			return (0);
		}
		ft_memdel((void **)&bin);
		i++;
	}
	ft_free_double((void **)path);
	return (1);
}

int			ft_exec(const char *buffer, t_argument *arguments)
{
	arguments->tokens = ft_tokenize(ft_strdup(buffer), arguments->env);
	if (arguments->tokens == NULL || arguments->tokens[0] == NULL)
	{
		ft_free_double((void **)arguments->tokens);
		return (1);
	}
	if (is_builtin(arguments))
		if (ft_bin_execute(arguments))
			ft_not_found(arguments->tokens[0]);
	ft_free_double((void **)arguments->tokens);
	return (0);
}

int			main(void)
{
	char		buffer[ARG_MAX + 1];
	int			re;
	t_argument	*arguments;

	arguments = ft_init_env();
	while (1)
	{
		ft_putstr("$> ");
		if ((re = read(0, buffer, ARG_MAX)) > 1)
		{
			buffer[re - 1] = '\0';
			if (ft_exec(buffer, arguments) == 1)
				continue ;
			ft_strclr(buffer);
		}
		else
			ft_putendl("");
	}
	return (0);
}
