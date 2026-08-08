/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:10:33 by anematol          #+#    #+#             */
/*   Updated: 2025/09/02 20:49:18 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;
	int		toggle_new_word;

	if (s[0] == '\0')
		return (0);
	count = 0;
	i = 0;
	toggle_new_word = 1;
	while (s[i] != '\0')
	{
		if (s[i] != c && toggle_new_word == 1)
		{
			count++;
			toggle_new_word = 0;
		}
		else if (s[i] == c && toggle_new_word == 0)
			toggle_new_word = 1;
		i++;
	}
	return (count);
}

static char	*ft_split_dup(char const *s, char c)
{
	size_t	j;
	size_t	word_len;
	char	*word;

	j = 0;
	while (s[j] != c && s[j] != '\0')
		j++;
	word_len = j;
	j = 0;
	word = (char *)malloc((word_len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (s[j] != c && s[j] != '\0')
	{
		word[j] = s[j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

static void	free_str_array(char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i])
	{
		free(str_array[i]);
		i++;
	}
	free(str_array);
}

char	**ft_split(char const *s, char c)
{
	size_t	curr_word;
	char	**words;
	int		toggle_new_word;

	words = (char **)ft_calloc((ft_count_words(s, c) + 1), sizeof(char *));
	if (!s || !words)
		return (free(words), NULL);
	curr_word = 0;
	toggle_new_word = 1;
	while (*s != '\0')
	{
		if (*s != c && toggle_new_word == 1)
		{
			words[curr_word] = ft_split_dup(s, c);
			if (!words[curr_word])
				return (free_str_array(words), NULL);
			toggle_new_word = 0;
			curr_word++;
		}
		else if (*s == c && toggle_new_word == 0)
			toggle_new_word = 1;
		s++;
	}
	return (words);
}
/*
int main()
{
	char *str = (char *)"aa\0bbb";//"ja hallo, hoerst du mich?";
	char c = '\0';
	int i = 0;

	char **split = ft_split(str, c);
	if (split != NULL)
	{
		while(split[i] != NULL)
		{
			printf("%s\n", split[i]);
			i++;
		}
	}
	else
		printf("NULL");
}
*/
