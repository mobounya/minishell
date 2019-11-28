/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 22:50:44 by mobounya          #+#    #+#             */
/*   Updated: 2019/11/28 22:53:12 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define TRUE (int8_t)1
#define FALSE (int8_t)0

typedef int8_t	t_BOOL;
extern char **environ;

t_BOOL	is_builtin(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t')
		i++;
	cmd[i] = '\0';
	i = 0;
	if (ft_strcmp(cmd, "echo") && ft_strcmp(cmd, "cd") && \
	ft_strcmp(cmd, "setenv") && ft_strcmp(cmd, "unsetenv") && \
	ft_strcmp(cmd, "env"))
	{
		free(cmd);
		return (FALSE);
	}
	else
	{
		free(cmd);
		return (TRUE);
	}
}

int		main(void)
{
	char	buffer[2048 + 1];
	int		re;

	re = 0;
	buffer[0] = 'c';
	while (1)
	{
		write(1, "$> ", 3);
		re = read(2, buffer, 2048);
		buffer[re - 1] = '\0';
		if (!ft_strcmp(buffer, "exit"))
			break ;
		if (is_builtin(ft_strdup(buffer)))
			ft_putendl("$> is builtin");
		else
			ft_putendl("$> System");
	}
}
