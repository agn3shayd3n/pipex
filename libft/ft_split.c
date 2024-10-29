/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agnesgar <agnesgar@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:49:02 by agnesgar          #+#    #+#             */
/*   Updated: 2024/04/05 12:39:20 by agnesgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// frees memory allocated for each of the strings in array given
static void	freestr(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}

static long	countwords(char const *str, char c)
{
	long	i;
	long	count;
	int		in_quotes;

	i = 0;
	count = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (str[i] == '"')
			in_quotes = !in_quotes;
		if (str[i] != c && !in_quotes)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
		i++;
	}
	return (count);
}

static char	*duplicate_word(char const *s, size_t *i, char c)
{
	size_t	start;
	char	*word;

	start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	word = ft_strndup(s + start, *i - start);
	return (word);
}

static char	**write_split(char const *s, char c, char **result)
{
	size_t	i;
	size_t	word;
	int		in_quotes;

	i = 0;
	word = 0;
	in_quotes = 0;
	while (s[i])
	{
		if (s[i] == '"')
			in_quotes = !in_quotes;
		if (s[i] != c && !in_quotes)
		{
			result[word] = duplicate_word(s, &i, c);
			if (!result[word])
				return (freestr(result), NULL);
			word++;
		}
		else
			i++;
	}
	result[word] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc(sizeof(char *) * (countwords(s, c) + 1));
	if (!result)
		return (NULL);
	result = write_split(s, c, result);
	return (result);
}
