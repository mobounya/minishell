/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 01:08:11 by mobounya          #+#    #+#             */
/*   Updated: 2019/12/05 00:13:55 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static int		ft_count_args(char *cmd)
{
	uint	args;
	uint	i;
	t_BOOL	quote;
	t_BOOL	word;

	quote = FALSE;
	i = 0;
	args = 0;
	word = FALSE;

	while (cmd[i])
	{
		if (cmd[i] == '"')
		{
			if (quote == TRUE)
			{
				args++;
				quote = FALSE;
			}
			else
				quote = TRUE;
		}
		else if (!quote && (cmd[i] == ' ' || cmd[i] == '\t'))
		{
			(word && args++);
			word = FALSE;
		}
		else if (!quote)
			word = TRUE;
		i++;
	}
	if (quote)
		return (-1);
	(word && args++);
	return (args);
}

char	*ft_dup_till(char *cmd, char c, uint *j)
{
	uint	i;
	char	*command;

	i = 0;
	while (cmd[i] && cmd[i] != c)
		i++;
	cmd[i] = '\0';
	*j = i + *j;
	command = ft_strdup(cmd);
	free(cmd);
	return (command);
}

char	*ft_search_vr(char **env, char *vr)
{
	char	*sign;
	uint	i;
	char	*copy;

	i = 0;
	while (env[i])
	{
		sign = ft_strrchr(env[i], '=');
		if (sign != NULL)
		{
			copy = ft_strdup(env[i]);
			copy[sign - env[i]] = '\0';
			if (!ft_strcmp(vr, copy))
			{
				ft_memdel((void**)&copy);
				return (ft_strdup(sign + 1));
			}
			ft_memdel((void**)&copy);
		}
		i++;
	}
	free(env);
	return (NULL);
}

char	**ft_tokenize(char *cmd, char **env)
{
	char	**tokens;
	int		args;
	uint	i;
	uint	j;
	char	*tmp;
	char	*path;

	i = 0;
	j = 0;
	args = ft_count_args(cmd);
	if (args == -1)
	{
		ft_putendl("Syntax Error");
		return (NULL);
	}
	tokens = malloc(sizeof(char *) * (args + 1));
	tokens[args] = NULL;
	while (cmd[i])
	{
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
			i++;
		if (cmd[i] == '"')
		{
			tokens[j] = ft_dup_till(ft_strdup(cmd + i + 1), '"', &i);
			i = i + 2;
			j++;
		}
		else if (cmd[i])
		{
			tokens[j] = ft_dup_till(ft_strdup(cmd + i), ' ', &i);
			j++;
		}
	}
	free(cmd);
	i = 1;
	while (tokens[i])
	{
		if (tokens[i][0] == '$')
		{
			if (!(tokens[i] = ft_search_vr(env, tokens[i] + 1)))
				tokens[i] = ft_strnew(1);
		}
		else if (tokens[i][0] == '~')
		{
			if (ft_strlen(tokens[i]) > 1 && tokens[i][1] != '/')
				continue;
			tmp = ft_strdup(tokens[i] + 1);
			path = ft_strjoin(env[2] + 5, tmp);
			free(tmp);
			free(tokens[i]);
			tokens[i] = path;
		}
		i++;
	}
	return (tokens);
}
