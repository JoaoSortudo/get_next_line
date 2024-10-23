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

char	*extract_line(char **remembrall)
{
	char	*line;
	char	*nl_position;
	size_t	line_len;

	//O PROBLEMA DE TUDO ESTÁ AQUI, PRECISAMOS DE UM TRATAMENTO ESPECIAL PARA 
	//A ÚLTIMA LINHA DO ARQUIVO, QUE PODE OU NÃO TERMINAR EM \n!!!!! 
	nl_position = ft_strchr(*remembrall, '\n');
	if (!nl_position)
		return (NULL);
	line_len = nl_position - *remembrall + 1;
	line = ft_substr(*remembrall, 0, line_len);
	*remembrall = ft_strdup(nl_position + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remembrall;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;

	bytes_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remembrall)
		remembrall = ft_strdup("");
	while (bytes_read >= 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < -1)
			return (NULL);
		buffer[bytes_read] = '\0';
		remembrall = ft_strjoin(remembrall, buffer);
		if (ft_strchr(remembrall, '\n') || bytes_read == 0)
			return (line = extract_line(&remembrall));
	}
	if (bytes_read <= 0)
		return (0);
	return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
int	main(void)
{
	int		fd = open("teste.txt", O_RDONLY);
	char	*line;

	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	// //line = get_next_line(fd);
	// while ((line = get_next_line(fd)) != NULL)
	// {
	// 	printf("%s", line);
	// 	free(line);
	// 	//line = get_next_line(fd);
	// }
	close(fd);
	return (0);
}
