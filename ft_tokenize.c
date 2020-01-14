/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 01:08:11 by mobounya          #+#    #+#             */
/*   Updated: 2020/01/14 23:53:23 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

void			ft_replace_home(char **str, char **env)
{
	char	*home;
	char	*after;
	char	*temp;

	home = ft_search_vr(env, "HOME");
	if (home == NULL)
		home = ft_strdup("~");
	if (*str + 1)
	{
		after = ft_strdup(*str + 1);
		temp = home;
		home = ft_strjoin(home, after);
		free(temp);
	}
	*str = home;
}

char			*ft_replace_env_var(const char *argument, char **env)
{
	char	*dollar;
	char	*var_name;
	char	*var_value;
	char	*res;
	uint	i;

	res = ft_strnew(0);
	while (*argument)
	{
		i = 0;
		if ((dollar = ft_strchr(argument, '$')) == NULL)
			break ;
		dollar++;
		while (dollar[i] && ft_isalnum(dollar[i]))
			i++;
		var_name = ft_strsub(dollar, 0, i);
		if ((var_value = ft_search_vr(env, var_name)) == NULL)
			var_value = ft_strnew(0);
		ft_strdel(&var_name);
		res = joinfree(res, ft_strsub(argument, 0, dollar - argument - 1), 3);
		res = joinfree(res, var_value, 3);
		argument = dollar + i;
	}
	res = joinfree(res, argument, 1);
	return (res);
}

void			ft_replace(char **tokens, char **env)
{
	char	*temp;

	while (*tokens)
	{
		if ((*tokens[0] == '~' && ft_strlen(*tokens) < 2) || \
			(*tokens[0] == '~' && *tokens[1] == '/'))
			ft_replace_home(&(*tokens), env);
		temp = *tokens;
		*tokens = ft_replace_env_var(*tokens, env);
		free(temp);
		tokens++;
	}
}

char			**ft_tokenize(char *cmd, char **env)
{
	char	**tokens;
	int		arg_count;

	arg_count = ft_count_args(cmd);
	if (arg_count == -1)
	{
		ft_putendl("Syntax Error");
		free(cmd);
		return (NULL);
	}
	if ((tokens = malloc(sizeof(char *) * (arg_count + 1))) == NULL)
		return (NULL);
	tokens[arg_count] = NULL;
	ft_split_args(tokens, cmd);
	ft_strlower(tokens[0]);
	ft_replace(tokens, env);
	free(cmd);
	return (tokens);
}
