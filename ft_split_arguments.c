/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 21:30:33 by mobounya          #+#    #+#             */
/*   Updated: 2020/01/14 21:30:59 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static char		*ft_get_sub(char **tokens, char c, const char *str)
{
	char	*char_ptr;

	char_ptr = ft_strchr(str, c);
	*tokens = ft_strsub(str, 0, char_ptr - str);
	return (char_ptr + 1);
}

void			ft_split_args(char **tokens, const char *command)
{
	uint	tokens_i;
	uint	i;

	tokens_i = 0;
	while (*command)
	{
		if (*command == '\"' || *command == '\'')
			command = ft_get_sub(tokens + tokens_i++, *command, command + 1);
		else
		{
			i = 0;
			while (*command && IS_WS(*command))
				command++;
			if (*command != '\'' && *command != '\"')
			{
				while (command[i] && !IS_WS(command[i]) && \
				command[i] != '\"' && command[i] != '\'')
					i++;
				tokens[tokens_i++] = ft_strsub(command, 0, i);
				command = command + i;
			}
		}
	}
	tokens[tokens_i] = NULL;
}
