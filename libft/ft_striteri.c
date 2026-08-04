/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:45:21 by anematol          #+#    #+#             */
/*   Updated: 2025/05/27 15:57:22 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		(*f)(i, &(s[i]));
		i++;
	}
}
/*
void func(unsigned int i, char *c)
{
	*c = *c + (char)i;
}

int main()
{
	char *str = "aaaaaaaaa";
	char *dup;
	dup = ft_strdup(str);
	ft_striteri(dup, &func);

	printf ("%s\n", dup);
}
*/
