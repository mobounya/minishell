/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 21:23:04 by mobounya          #+#    #+#             */
/*   Updated: 2020/01/14 21:24:30 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

void		ft_errors(char *prefix)
{
	static char *errors[] = {
		"Undefined error: 0",
		"no such file or directory",
		"too many arguments",
		"permission denied",
		"not a directory",
		NULL,
	};

	if (g_errno > 4)
	{
		ft_putendl("Undefined error: ");
		ft_putnbr(g_errno);
		ft_putchar('\n');
		return ;
	}
	if (prefix)
	{
		ft_putstr(prefix);
		ft_putstr(": ");
	}
	ft_putendl(errors[g_errno]);
}

void		ft_not_found(char *command)
{
	ft_putstr("minishell: ");
	ft_putstr("Command Not Found: ");
	ft_putendl(command);
}
