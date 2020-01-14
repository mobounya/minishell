/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 21:25:13 by mobounya          #+#    #+#             */
/*   Updated: 2020/01/14 21:25:44 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

void		ft_free_double(void **ptr)
{
	uint i;

	i = 0;
	if (ptr == NULL)
		return ;
	while (ptr[i])
	{
		ft_memdel((void **)&ptr[i]);
		i++;
	}
	ft_memdel((void **)&ptr);
}
