/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:17:55 by anematol          #+#    #+#             */
/*   Updated: 2025/05/23 11:57:06 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = ft_strlen(s);
	i = 0;
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (i <= len)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}
/*
int main()
{
	char *s = "hallo";

	char *s_1 = ft_strdup(s);

	printf("%s\n", s);
	printf("%p\n", s);
	printf("%s\n", s_1);
	printf("%p\n", s_1);
}
*/
