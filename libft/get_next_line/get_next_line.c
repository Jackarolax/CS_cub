/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:34:58 by anematol          #+#    #+#             */
/*   Updated: 2026/10/03 11:54:57 by anematol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_lf(char *str, int with_lf)
{
	int	i;

	i = 0;
	if (with_lf)
	{
		while (str[i] != '\0' && str[i] != '\n')
		{
			i++;
		}
		if (str[i] == '\n')
			i++;
		return (i);
	}
	else
	{
		while (str[i] != '\0')
		{
			i++;
		}
		return (i);
	}
}

char	*ft_add_buf(char *line, char *buf)
{
	int		len;
	int		next_len;
	char	*temp;
	int		i;

	i = -1;
	len = ft_strlen_lf(line, 0);
	next_len = ft_strlen_lf(buf, 1);
	temp = (char *)malloc((len + next_len + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	while (++i < len)
		temp[i] = line[i];
	i = 0;
	while (i < next_len)
	{
		temp[len + i] = buf[i];
		i++;
	}
	temp[len + i] = '\0';
	free(line);
	buf = ft_update_buf(buf, next_len);
	return (temp);
}

int	ft_lf_in_buf(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_update_buf(char *buf, int delete_up_to)
{
	int	i;

	i = 0;
	while (buf[delete_up_to + i] != '\0')
	{
		buf[i] = buf[delete_up_to + i];
		i++;
	}
	while (i < BUFFER_SIZE + 1)
	{
		buf[i] = '\0';
		i++;
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	buf[BUFFER_SIZE + 1];
	int			bytes_read;

	line = (char *)malloc(sizeof(char));
	if (!line || (read(fd, 0, 0) < 0) || BUFFER_SIZE <= 0 || fd < 0)
		return (free(line), NULL);
	line[0] = '\0';
	if (buf[0] == '\0')
		bytes_read = read(fd, buf, BUFFER_SIZE);
	if (buf[0] == '\0' && bytes_read == 0)
		return (free(line), NULL);
	while (!ft_lf_in_buf(buf) && buf[0] != '\0')
	{
		line = ft_add_buf(line, buf);
		if (!line)
			return (free(line), NULL);
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	if (buf[0] != '\0')
		line = ft_add_buf(line, buf);
	if (!line)
		return (free(line), NULL);
	return (line);
}
