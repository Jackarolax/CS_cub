/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssin <ssin@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:00:38 by ssin              #+#    #+#             */
/*   Updated: 2025/07/11 17:04:55 by ssin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	n;
	size_t	s_len;
	char	*substr;

	if (!s)
		return (NULL);
	n = 0;
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	while (n < len)
	{
		substr[n] = s[start + n];
		n++;
	}
	substr[n] = '\0';
	return (substr);
}

static void	free_memo(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static int	read_to_stash(int fd, char **stash, char **newline_pos)
{
	char	*buffer;
	char	*after_nl;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free_memo(stash), -1);
		buffer[bytes_read] = '\0';
		if (!*stash)
			*stash = ft_strdup("");
		after_nl = ft_strjoin(*stash, buffer);
		if (!after_nl)
			return (free(buffer), -1);
		free(*stash);
		*stash = after_nl;
		*newline_pos = ft_strchr(*stash, '\n');
		if (*newline_pos || bytes_read == 0)
			break ;
	}
	return (free(buffer), bytes_read);
}

static char	*extract_line(char **stash, char *newline_pos)
{
	char	*line;
	char	*after_nl;

	if (newline_pos)
	{
		line = ft_substr(*stash, 0, newline_pos - *stash + 1);
		after_nl = ft_strdup(newline_pos + 1);
		free_memo(stash);
		*stash = after_nl;
		if (*stash && !(*stash)[0])
			free_memo(stash);
	}
	else
	{
		line = ft_strdup(*stash);
		free_memo(stash);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*newline_pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_to_stash(fd, &stash, &newline_pos) < 0)
		return (NULL);
	if (!stash || !stash[0])
	{
		free_memo(&stash);
		return (NULL);
	}
	return (extract_line(&stash, newline_pos));
}

/*
int	main(void)
{
	char	*n;
	int		opened_file;
	opened_file = open("41_with_nl", O_RDONLY);
	n = get_next_line(opened_file);
	printf("%s", n);
	n = get_next_line(opened_file);
	printf("%s", n);
	n = get_next_line(opened_file);
	printf("%s", n);
	n = get_next_line(opened_file);
	printf("%s", n);
	n = get_next_line(opened_file);
	printf("%s", n);
	n = get_next_line(opened_file);
	printf("%s", n);
	return (0);
}*/
