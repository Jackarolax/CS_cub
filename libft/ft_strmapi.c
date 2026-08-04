/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:28:42 by anematol          #+#    #+#             */
/*   Updated: 2025/05/27 15:54:34 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*return_str;

	return_str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!return_str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		return_str[i] = (*f)(i, s[i]);
		i++;
	}
	return_str[i] = '\0';
	return (return_str);
}
/*
char func(unsigned int i, char c)
{
	return (c + (char)i);
}

int main()
{
	char *str = "aaaaaaaaa";
	char *mapped_str = ft_strmapi(str, &func);

	printf ("%s\n", mapped_str);
}
*/
