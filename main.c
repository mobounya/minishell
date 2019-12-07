/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 22:50:44 by mobounya          #+#    #+#             */
/*   Updated: 2019/12/07 20:13:42 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

extern char **environ;

void	ft_free_double(char	**ptr)
{
	uint i;

	i = 0;
	if (ptr == NULL)
		return ;
	while (ptr[i])
	{
		ft_memdel((void**)&ptr[i]);
		i++;
	}
	ft_memdel((void**)&ptr);
}

int		ft_exit(t_argument	*arguments)
{
	uint i;
	int status;

	i = 0;
	status = 0;
	while (arguments->tokens[i])
		i++;
	if (i > 2)
	{
		ft_putendl("exit: too many arguments");
		return (1);
	}
	else if (arguments->tokens[1])
		status = ft_atoi(arguments->tokens[1]);
	exit(status);
	return (0);
}

int		ft_echo(t_argument	*arguments)
{
	int		i;
	t_BOOL	line;

	i = 1;
	line = TRUE;
	while (arguments->tokens[i] && arguments->tokens[i][0] == '-')
	{
		if (!ft_strcmp(arguments->tokens[i], "-n"))
			line = FALSE;
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

int		ft_changedir(t_argument	*arguments)
{
	uint	i;
	char	*home;

	i = 0;
	while (arguments->tokens[i]) 
		i++;
	if (i == 1)
	{
		home = ft_search_vr(arguments->env, ft_strdup("HOME"));
		chdir(home);
		free(home);
	}
	else if (i > 2)
		ft_putendl("cd: too many arguments");
	else
		chdir(arguments->tokens[1]);
	return (1);
}

int		ft_replace_env(t_argument *arguments)
{
	uint	j;
	char	**token;
	char	**variable;


	j = 0;
	if (ft_strchr(arguments->tokens[1], '='))
	{
		token = ft_strsplit(arguments->tokens[1], '=');
		while (arguments->env[j])
		{
			variable = ft_strsplit(arguments->env[j], '=');
			if (ft_strcmp(variable[0], token[0]) == 0)
			{
				ft_free_double(variable);
				arguments->env[j] = ft_strdup(arguments->tokens[1]);
				ft_free_double(token);
				return (0);
			}
			ft_free_double(variable);
			j++;
		}
		ft_free_double(token);
	}
	return (1);
}

int		ft_setenv(t_argument *arguments)
{
	uint	size;
	char	**tmp;

	size = 0;
	while (arguments->tokens[size])
		size++;
	if (size == 1)
	{
		ft_putendl("Usage: setenv VARIABLE=VALUE");
		return (1);
	}
	else if (size > 2)
	{
		ft_putendl("setenv: too many arguments");
		return (1);
	}
	else if (ft_replace_env(arguments))
	{
		size = 0;
		while (arguments->env[size])
			size++;
		tmp = malloc(sizeof(char *) * (size + 2));
		tmp[size + 1] = NULL;
		size = 0;
		while (arguments->env[size])
		{
			tmp[size] = ft_strdup(arguments->env[size]);
			size++;
		}
		tmp[size] = ft_strdup(arguments->tokens[1]);
		ft_free_double(arguments->env);
		arguments->env = tmp;
	}
	return (0);
}

int		ft_env(t_argument	*arguments)
{
	uint i;

	i = 0;
	while (arguments->env[i])
		ft_putendl(arguments->env[i++]);
	return (0);
}

void	ft_init_env(t_argument	*arguments)
{
	uint	i;
	char	**res;

	i = 0;
	while (environ[i])
		i++;
	res = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (environ[i])
	{
		res[i] = ft_strdup(environ[i]);
		i++;
	}
	res[i] = NULL;
	arguments->env = res;
}

int		ft_unsetenv(t_argument	*arguments)
{
	uint	i;
	uint	j;
	char	*tmp;
	char	*sign;
	char	**new;

	i = 0;
	j = 0;
	while (arguments->env[i])
		i++;
	if (arguments->env[1] == NULL)
	{
		ft_putendl("Usage: unsetenv $VAR");
		return (1);
	}
	new = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (arguments->env[i])
	{
		tmp = ft_strdup(arguments->env[i]);
		sign = ft_strchr(tmp, '=');
		tmp[sign - tmp] = '\0';
		if (ft_strcmp(tmp, arguments->tokens[1]))
		{
			new[j] = ft_strdup(arguments->env[i]);
			j++;
		}
		i++;
	}
	new[j] = NULL;
	ft_free_double(arguments->env);
	arguments->env = new;
	return (1);
}

int		is_builtin(t_argument	*arguments)
{
	uint i;

	i = 0;
	const t_builtin_matcher builtin_tab[6] = 
	{
		{.name="exit", .function = &ft_exit},
		{.name="echo", .function = &ft_echo},
		{.name="cd", .function= &ft_changedir},
		{.name="setenv", .function=&ft_setenv},
		{.name="unsetenv", .function=&ft_unsetenv},
		{.name="env", .function=&ft_env},
	};
	while (i < 6)
	{
		if (!ft_strcmp(builtin_tab[i].name, arguments->tokens[0]))
			if (builtin_tab[i].function)
			{
				builtin_tab[i].function(arguments);
				return (0);
			}
		i++;
	}
	return (1);
}

int		main(void)
{
	char		buffer[ARG_MAX + 1];
	int			re;
	int			pid;
	t_argument	*arguments;

	arguments = ft_memalloc(sizeof(t_argument));
	ft_init_env(arguments);
	while (1)
	{
		write(1, "$> ", 3);
		if ((re = read(2, buffer, ARG_MAX)) > 1)
		{
			buffer[re - 1] = '\0';
			arguments->tokens = ft_tokenize(ft_strdup(buffer), arguments->env);
			if (arguments->tokens == NULL || arguments->tokens[0] == NULL)
			{
				ft_free_double(arguments->tokens);
				continue;
			}
			if (is_builtin(arguments))
			{
				if (!ft_strcmp(arguments->tokens[0], "pwd"))
				{
					pid = fork();
					if (pid == 0)
						execve("/bin/pwd", arguments->tokens, arguments->env);
					else
						wait(NULL);
				}
			}
			ft_memset(buffer, '\0', ARG_MAX);
			ft_free_double(arguments->tokens);
		}
	}
	return (0);
}
