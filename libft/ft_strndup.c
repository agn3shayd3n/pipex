/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agnesgar <agnesgar@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 11:16:06 by agnesgar          #+#    #+#             */
/*   Updated: 2024-10-29 11:16:06 by agnesgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	size_t	to_copy;
	char	*dup;

	len = ft_strlen(s);
	if (len < n)
		to_copy = len;
	else
		to_copy = n;
	dup = malloc(to_copy + 1);
	if (dup == NULL)
		return (NULL);
	ft_memcpy(dup, s, to_copy);
	dup[to_copy] = '\0';
	return (dup);
}
