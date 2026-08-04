/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:30:05 by anematol          #+#    #+#             */
/*   Updated: 2025/05/28 14:02:49 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		str_len;
	char		*substr;
	size_t		i;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start > str_len)
		return ((char *)ft_calloc(1, sizeof(char)));
	i = 0;
	if (((size_t)start + len) > str_len)
		len = str_len - (size_t)start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (i < len)
	{
		substr[i] = s[(size_t)start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
/*
int main()
{
	char *big = "hallo was geht ab";
	char *little = "was";

	char *sub;
	sub = ft_substr(big, 6, 3);

	printf("%s\n", sub);
	printf("%s\n", little);
}

*/
