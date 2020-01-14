/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 21:03:38 by mobounya          #+#    #+#             */
/*   Updated: 2020/01/14 21:04:27 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strndup(char *str, unsigned int n)
{
	unsigned int	i;
	char			*res;

	if ((res = malloc(sizeof(char) * n + 1)) == NULL)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
