/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 22:57:35 by yamrire           #+#    #+#             */
/*   Updated: 2022/02/27 23:42:17 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

int	new_line_index (char *str)
{
	int	index;

	index = 0;
	while (str[index] && str[index] != '\n')
		index++;
	return (index);
}

char *return_line(char **stash, int rd, char *buff)
{
	char	*tmp;
	char	*tmp_1;
	int		len;

	free (buff);
	if (rd < 0 || !(*stash))
		return (NULL);
	len = new_line_index(*stash);
	tmp = ft_substr(*stash, 0, len + 1);
	tmp_1 = ft_substr(*stash, len + 1, ft_strlen(*stash) - len);
	free (*stash);
	if (tmp_1[0] == '\0')
	{
		free (tmp_1);
		*stash = NULL;
	}
	else
		*stash = tmp_1;
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*buff;
	char		*line;
	int			rd;

	if (fd < 0)
		return (NULL);
	buff = malloc (BUFFER_SIZE + 1);
	rd = read(fd, buff, BUFFER_SIZE);
	while (rd > 0)
	{
		buff[rd] = '\0';
		if (!stash[fd])
			stash[fd] = ft_strdup(buff);
		else if (buff)
		{
			line = ft_strjoin(stash[fd], buff);
			free (stash[fd]);
			stash[fd] = line;
		}
		if (ft_strchr(stash[fd], '\n') != NULL)
			break ;
		rd = read(fd, buff, BUFFER_SIZE);
	}
	return (return_line(&stash[fd], rd, buff));
}
