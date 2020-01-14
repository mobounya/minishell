/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 03:17:45 by mobounya          #+#    #+#             */
/*   Updated: 2020/01/06 04:08:53 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_double(void **ptr)
{
	unsigned int	i;

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
