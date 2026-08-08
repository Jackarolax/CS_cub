/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:03:29 by anematol          #+#    #+#             */
/*   Updated: 2025/05/27 18:24:55 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*memory;
	size_t			i;

	i = 0;
	memory = malloc(nmemb * size);
	if (!memory)
		return (NULL);
	while (i < (nmemb * size))
	{
		memory[i] = 0;
		i++;
	}
	return ((void *)memory);
}
/*
int main()
{
	int *ptr = ft_calloc(5, sizeof(int));
	int i = 0;

	while (i < 5)
	{
		printf("%i", ptr[i]);
		i++;
	}
}
*/
