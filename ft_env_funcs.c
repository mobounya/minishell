/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 21:18:47 by mobounya          #+#    #+#             */
/*   Updated: 2020/01/14 21:21:30 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int			ft_compare_env(char *env, char *var)
{
	char *tmp;
	char *sign;

	tmp = ft_strdup(env);
	sign = ft_strchr(tmp, '=');
	tmp[sign - tmp] = '\0';
	if (ft_strcmp(tmp, var))
	{
		free(tmp);
		return (0);
	}
	else
	{
		free(tmp);
		return (1);
	}
}

int			ft_replace_env(t_argument *arguments)
{
	uint j;
	char **token;
	char **variable;

	j = 0;
	if (ft_strchr(arguments->tokens[1], '='))
	{
		token = ft_strsplit(arguments->tokens[1], '=');
		while (arguments->env[j])
		{
			variable = ft_strsplit(arguments->env[j], '=');
			if (ft_strcmp(variable[0], token[0]) == 0)
			{
				ft_free_double((void **)variable);
				free(arguments->env[j]);
				arguments->env[j] = ft_strdup(arguments->tokens[1]);
				ft_free_double((void **)token);
				return (0);
			}
			ft_free_double((void **)variable);
			j++;
		}
		ft_free_double((void **)token);
	}
	return (1);
}

t_argument	*ft_init_env(void)
{
	uint		i;
	char		**res;
	t_argument	*arguments;
	extern char	**environ;

	arguments = malloc(sizeof(arguments));
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
	return (arguments);
}

int			ft_env(t_argument *arguments)
{
	uint i;

	i = 0;
	while (arguments->env[i])
		ft_putendl(arguments->env[i++]);
	return (0);
}
