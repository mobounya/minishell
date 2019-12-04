/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 22:50:44 by mobounya          #+#    #+#             */
/*   Updated: 2019/12/05 00:49:06 by mobounya         ###   ########.fr       */
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

	i = 0;
	while (arguments->tokens[i]) 
		i++;
	if (i == 1)
		chdir(environ[3] + 5);
	else if (i > 2)
		ft_putendl("cd: too many arguments");
	else
		chdir(arguments->tokens[1]);
	return (1);
}

int		ft_setenv(char *var, char ***env)
{
	char	**new;
	uint	i;
	char	**tmp;

	tmp = *env;
	i = 0;
	while (tmp[i])
		i++;
	i = i + 1;
	new = malloc(sizeof(char *) * (i + 1));
	new[i] = NULL;
	i = 0;
	while(tmp[i])
	{
		new[i] = ft_strdup(tmp[i]);
		i++;
	}
	new[i] = ft_strdup(var);
	*env = new;
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


int		is_builtin(t_argument	*arguments)
{
	uint i;

	i = 0;
	const t_builtin_matcher builtin_tab[6] = 
	{
		{.name="exit", .function = &ft_exit},
		{.name="echo", .function = &ft_echo},
		{.name="cd", .function= &ft_changedir},
		{.name="setenv", .function=NULL},
		{.name="unsetenv", .function=NULL},
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
	char	buffer[ARG_MAX + 1];
	int		re;
	int		pid;
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
						execve("/bin/echo", arguments->tokens, arguments->env);
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
