/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:35:37 by mobounya          #+#    #+#             */
/*   Updated: 2020/01/10 22:59:03 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_new_len(const char *str, const char *needle, const char *sub)
{
	size_t	size;
	size_t	size_sub;
	size_t	size_needle;
	int		needle_count;
	char	*p_needle;

	size = ft_strlen(str);
	if (needle[0] == '\0')
		return (size);
	size_sub = ft_strlen(sub);
	size_needle = ft_strlen(needle);
	needle_count = 0;
	while (*str)
	{
		if ((p_needle = ft_strstr(str, needle)) == NULL)
			break ;
		needle_count++;
		str = p_needle + size_needle;
	}
	return ((size - (size_needle * needle_count)) + (size_sub * needle_count));
}

char	*ft_strreplace(char *str, const char *needle, const char *sub)
{
	char	*res;
	char	*p_needle;
	size_t	size_needle;
	size_t	size_sub;
	char	*cursor;

	if ((res = ft_strnew(ft_new_len(str, needle, sub))) == NULL)
		return (NULL);
	size_needle = ft_strlen(needle);
	size_sub = ft_strlen(sub);
	cursor = res;
	if (needle[0] != '\0')
		while (*str)
		{
			if ((p_needle = ft_strstr(str, needle)) == NULL)
				break ;
			ft_strncpy(cursor, str, p_needle - str);
			cursor += p_needle - str;
			str = str + (p_needle - str);
			ft_strcpy(cursor, sub);
			cursor += size_sub;
			str += size_needle;
		}
	ft_strcpy(cursor, str);
	return (res);
}
