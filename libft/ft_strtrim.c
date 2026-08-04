/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:17:16 by anematol          #+#    #+#             */
/*   Updated: 2025/05/30 09:28:08 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char_in_str(char c, char const *s)
{
	if (c == '\0')
		return (1);
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		trimstart;
	int		trimend;
	int		i;
	char	*trim_str;

	trimstart = 0;
	trimend = 0;
	i = 0;
	while (ft_char_in_str(s1[i], set))
		i++;
	trimstart = i;
	i = ft_strlen(s1) - 1;
	while (ft_char_in_str(s1[i], set))
		i--;
	trimend = i;
	trim_str = ft_substr(s1, trimstart, trimend - trimstart + 1);
	return (trim_str);
}
/*
int main ()
{
	char *str = "aaaaaaaaaaaaaaaaHalloabababbbabba";
	char *set = "ab";

	char *trimmed = ft_strtrim(str, set);
	printf("%s\n", trimmed);
}
*/
