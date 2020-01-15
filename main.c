/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 22:50:44 by mobounya          #+#    #+#             */
/*   Updated: 2020/01/15 19:37:20 by mobounya         ###   ########.fr       */
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
				ft_errors(g_builtin_tab[i].name, 1);
			return (0);
		}
		i++;
	}
	return (1);
}

int			ft_exec(const char *buffer, t_argument *arguments)
{
	g_errno = 0;
	arguments->tokens = ft_tokenize(ft_strdup(buffer), arguments->env);
	if (arguments->tokens == NULL || arguments->tokens[0] == NULL)
	{
		ft_free_double((void **)arguments->tokens);
		return (1);
	}
	if (is_builtin(arguments))
	{
		if ((g_errno = ft_bin_execute(arguments)))
		{
			if (g_errno == 1)
				ft_not_found(arguments->tokens[0]);
			else if (g_errno == 2)
				ft_file_not_found(arguments->tokens[0]);
			else
			{
				ft_errors("minishell", 0);
				ft_putstr(": ");
				ft_putendl(arguments->tokens[0]);
			}
		}
	}
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
