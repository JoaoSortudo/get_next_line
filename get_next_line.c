/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpires-n <jpires-n@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-22 12:45:12 by jpires-n          #+#    #+#             */
/*   Updated: 2024-10-22 12:45:12 by jpires-n         ###   ########.rio      */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*please_free(char *to_be_freed)
{
	free(to_be_freed);
	return (NULL);
}

char	*extract_line(char **remembrall)
{
	char	*line;
	char	*nl_position;
	char	*temp;
	size_t	line_len;

	temp = 0;
	nl_position = ft_strchr(*remembrall, '\n');
	if (nl_position)
	{
		line_len = nl_position - *remembrall + 1;
		line = ft_substr(*remembrall, 0, line_len);
		temp = *remembrall;
		*remembrall = ft_strdup(nl_position + 1);
		free(temp);
		return (line);
	}
	if (**remembrall)
	{
		line = ft_strdup(*remembrall);
		free(*remembrall);
		*remembrall = NULL;
		return (line);
	}
	return (NULL);
}

char	*read_and_return(int fd, char **remembrall)
{
	char		*temp;
	char		*buffer;
	ssize_t		bytes_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (please_free(buffer));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (please_free(buffer));
		buffer[bytes_read] = '\0';
		temp = *remembrall;
		*remembrall = ft_strjoin(*remembrall, buffer);
		free(temp);
		if (ft_strchr(*remembrall, '\n'))
			break ;
	}
	if (bytes_read < 0)
		return (please_free(buffer));
	free(buffer);
	return (*remembrall);
}

char	*get_next_line(int fd)
{
	static char	*remembrall;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remembrall)
		remembrall = ft_strdup("");
	if (!read_and_return(fd, &remembrall))
		return (NULL);
	if (*remembrall)
		return (extract_line(&remembrall));
	free(remembrall);
	remembrall = NULL;
	return (NULL);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <fcntl.h>
// int	main(void)
// {
// 	int		fd = open("teste.txt", O_RDONLY);
// 	char	*line;

// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	// //line = get_next_line(fd);
// 	// while ((line = get_next_line(fd)) != NULL)
// 	// {
// 	// 	printf("%s", line);
// 	// 	free(line);
// 	// 	//line = get_next_line(fd);
// 	// }
// 	close(fd);
// 	return (0);
// }
