/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:10:38 by anematol          #+#    #+#             */
/*   Updated: 2025/05/27 16:49:18 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*result_str;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result_str = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!result_str)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		result_str[i] = s1[i];
		i++;
	}
	while ((i - s1_len) < s2_len)
	{
		result_str[i] = s2[i - s1_len];
		i++;
	}
	result_str[i] = '\0';
	return (result_str);
}
