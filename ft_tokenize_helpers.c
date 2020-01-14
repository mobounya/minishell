/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 01:10:53 by mobounya          #+#    #+#             */
/*   Updated: 2020/01/14 21:39:47 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

char	*ft_match_char(char *str, char c)
{
	char	*char_index;

	char_index = ft_strchr(str, c);
	if (char_index == NULL)
		return (NULL);
	return (char_index + 1);
}

int		ft_count_args(char *command)
{
	uint	count;
	uint	word;

	count = 0;
	word = 1;
	while (*command)
	{
		if (*command == '\"' || *command == '\'')
		{
			if ((command = ft_match_char(command + 1, *command)) == NULL)
				return (-1);
			count++;
		}
		else
		{
			if (!IS_WS(*command) && word)
				(++count && (word = 0));
			else if (IS_WS(*command))
				word = 1;
			command++;
		}
	}
	return (count);
}

char	*ft_search_vr(char **env, char *var)
{
	char	*sign;
	uint	i;
	char	*copy;

	var = (var[0] == '$') ? var + 1 : var;
	i = -1;
	while (env[++i])
	{
		if ((sign = ft_strchr(env[i], '=')) != NULL)
		{
			copy = ft_strdup(env[i]);
			copy[sign - env[i]] = '\0';
			if (!ft_strcmp(var, copy))
			{
				ft_memdel((void**)&copy);
				return (ft_strdup(sign + 1));
			}
			ft_memdel((void**)&copy);
		}
	}
	return (NULL);
}

char	*joinfree(const char *a, const char *b, int flag)
{
	char	*str;

	str = ft_strjoin(a, b);
	if (flag == 1 || flag == 3)
		free((void*)a);
	if (flag == 2 || flag == 3)
		free((void*)b);
	return (str);
}
